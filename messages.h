#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include "kernel.h"
#include "kernel_data.h"

// =========================================== MESSAGE =========================================== //

static inline msg* nextMsg(const msg* const node) { return node->pNext; }
static inline msg* prevMsg(const msg* const node) { return node->pPrevious; }

static inline TaskNode* getTask(const msg* const m) { return m->pBlock; }
static inline void*     getData(const msg* const m) { return m->pData; }

static msg* createMsg(void* data) {
    msg* m = alloc(sizeof *m);
    m->pData = data;
    return m;
}

static void deleteMsg(msg* m) {
    delete(m->pData);
    delete(m);
}

static b32 setMessage(msg* const m, const void* data, i32 size) {
    if (!data || size < 1) { return 0; }
    delete(m->pData);
    
    if (m->pData = alloc(size), !m->pData) { return 0; }
    
    memcpy(m->pData, data, size);
    return 1;
}

// =========================================== MAILBOX =========================================== //

static inline i32 getDataSize   (const mailbox* const mBox)   { return mBox->nDataSize; }
static inline i32 getMsgMax     (const mailbox* const mBox)   { return mBox->nMaxMessages; }
static inline i32 getMsgCount   (const mailbox* const mBox)   { return mBox->nMessages; }

static inline msg* getFirstMsg  (const mailbox* const mBox)   { return mBox->pHead->pNext; }
static inline msg* getLastMsg   (const mailbox* const mBox)   { return mBox->pHead->pPrevious; }
static inline msg* getDummyMsg  (const mailbox* const mBox)   { return mBox->pHead; }

static void insertMsg(msg* const new, msg* const prev, msg* const next) {
    next->pPrevious = new;
    new->pNext      = next;
    new->pPrevious  = prev;
    prev->pNext     = new;
}

static msg* removeMsg(msg* const m) {
    msg* p       = m->pPrevious;
    msg* n       = m->pNext;
    p->pNext     = n;
    n->pPrevious = p;
    return m;
}

static b32 msgPushFront(mailbox* const mBox, msg* const m) {
    if (mBox->nMessages >= mBox->nMaxMessages) { return 0; }

    mBox->nMessages++;
    insertMsg(m, getDummyMsg(mBox), getFirstMsg(mBox));

    return 1;
}

static b32 msgPushBack (mailbox* const mBox, msg* const m) {
    if (mBox->nMessages >= mBox->nMaxMessages) { return 0; }

    mBox->nMessages++;
    insertMsg(m, getLastMsg(mBox), getDummyMsg(mBox));

    return 1;
}

static msg* msgPopFront (mailbox* const mBox) {
    mBox->nMessages--;
    return removeMsg(getFirstMsg(mBox));
}

static msg* msgPopBack  (mailbox* const mBox) {
    mBox->nMessages--;
    return removeMsg(getLastMsg(mBox));
}

mailbox* create_mailbox(uint maxMsg, uint dataSize) {
    mailbox* mBox   = alloc(sizeof *mBox);
    mBox->pHead     = alloc(sizeof *mBox->pHead);
    
    mBox->pHead->pNext      = mBox->pHead;
    mBox->pHead->pPrevious  = mBox->pHead;
    
    mBox->nDataSize     = dataSize;
    mBox->nMaxMessages  = maxMsg;
    
    return mBox;
}

int no_messages(mailbox* mBox) {
    return mBox->pHead->pNext == mBox->pHead;
}

exception remove_mailbox(mailbox* mBox) {
    if (!no_messages(mBox)) { return NOT_EMPTY; }
    delete(mBox->pHead);
    delete(mBox);
    return OK;
}

static inline b32 msgRecIsWaiting(const mailbox* mBox) { return mBox->nBlockedMsg < 0; }
static inline b32 msgSndIsWaiting(const mailbox* mBox) { return mBox->nBlockedMsg > 0; }

// NOTE: not tested
exception send_wait(mailbox* mBox, void* pData) {
    volatile int first = TRUE;
    isr_off();
    SaveContext();
    if (first) {
        first = FALSE;
        if (msgRecIsWaiting(mBox)) {
            setMessage(getFirstMsg(mBox), pData, getDataSize(mBox));
            msg* rec = msgPopFront(mBox);
            addTask_Deadline(readyList, getTask(rec));
            deleteMsg(rec);
        } else {
            msg* new = createMsg(pData); if (!new) { return FAIL; }
            msgPushBack(mBox, new);
            addTask_Deadline(waitList, removeNode(firstNode(readyList)));
            Running = firstNode(readyList)->pTask;
        }
        LoadContext();
    } else {
        if (deadline() <= ticks()) {
            isr_off();
            msg* m = msgPopFront(mBox);
            deleteMsg(m);
            isr_on();
            return DEADLINE_REACHED;
        } else {
            return OK;
        }
    }
}

// NOTE: not tested
exception receive_wait(mailbox* mBox, void* pData) {
    volatile int first = TRUE;
    isr_off();
    SaveContext();
    if (first) {
        first = FALSE;
        if (msgSndIsWaiting(mBox)) {
            memcpy(pData, getFirstMsg(mBox)->pData, getDataSize(mBox));
            msg* snd = msgPopFront(mBox);
            if (snd->pBlock != NULL) {
                addTask_Deadline(readyList, snd->pBlock);
                Running = getFirstNode(readyList)->pTask;
                deleteMsg(snd);
            } else {
                deleteMsg(snd);
            }
        } else {
            msg* new = createMsg(pData); if (!new) { return FAIL; }
            msgPushBack(mBox, new);
            addTask_Deadline(readyList, removeNode(firstNode(waitList)));
            Running = firstNode(readyList)->pTask;
        }
        LoadContext();
    } else {
        if (firstTask(waitList)->pTask->DeadLine <= ticks()) {
            isr_off();
            deleteMsg(msgPopFront(mBox));
            isr_on();
            return DEADLINE_REACHED;
        } else {
            return OK;
        }
    }
}



// NOTE: not tested
exception send_no_wait(mailbox* mBox, void* pData) {
    volatile int first = TRUE;
    isr_off();
    SaveContext();
    if (first) {
        first = FALSE;
        if (msgRecIsWaiting(mBox))  {
            setMessage(getFirstMsg(mBox), pData, getDataSize(mBox));
            msg* rec = msgPopFront(mBox);
            addTask_Deadline(readyList, getTask(rec));
            deleteMsg(rec);
            LoadContext();
        } else {
            msg* new = createMsg(pData); if (!new) { return FAIL; }
            if(isFull(mBox)) {
                deleteMsg(msgPopFront(mBox));
            }
            msgPushBack(mBox, new);
        }
    }
    return OK;
}

// NOTE: not tested
int receive_no_wait(mailbox* mBox, void* pData) {
    volatile int first = TRUE;
    isr_off();
    SaveContext();
    if (first)  {
        first = FALSE;
        if (msgSndIsWaiting(mBox)) {
            memcpy(pData, getFirstMsg(mBox)->pData, getDataSize(mBox));
            msg* snd = msgPopFront(mBox);
            if (snd->pBlock != NULL) {
                addTask_Deadline(readyList, snd->pBlock);
                Running = getFirstNode(readyList)->pTask;
                deleteMsg(snd);
            } else {
                deleteMsg(snd);
            }
        } else {
            msg* new = createMsg(pData); if (!new) { return FAIL; }
            msgPushBack(mBox, new);
            addTask_Deadline(readyList, removeNode(firstNode(waitList)));
            Running = firstNode(readyList)->pTask;
        }     
        LoadContext();
    }
    return OK;
}

#endif
