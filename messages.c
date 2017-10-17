#include "kernel_data.h"

// =========================================== MESSAGE =========================================== //

TaskNode* getTask(const msg* const m) { return m->pBlock; }
void*     getData(const msg* const m) { return m->pData; }

msg* createMsg(void* data, i32 size) {
    msg* m = alloc(sizeof *m);
    m->pData = data;
    return m;
}

// =========================================== MAILBOX =========================================== //

i32 getDataSize   (const mailbox* const mBox)   { return mBox->nDataSize; }

msg* getFirstMsg  (const mailbox* const mBox)   { return mBox->pHead->pNext; }
msg* getLastMsg   (const mailbox* const mBox)   { return mBox->pHead->pPrevious; }
msg* getDummyMsg  (const mailbox* const mBox)   { return mBox->pHead; }

void insertMsg(msg* const new, msg* const prev, msg* const next) {
    next->pPrevious = new;
    new->pNext      = next;
    new->pPrevious  = prev;
    prev->pNext     = new;
}

msg* removeMsg(msg* const m) {
    msg* p       = m->pPrevious;
    msg* n       = m->pNext;
    p->pNext     = n;
    n->pPrevious = p;
    return m;
}

b32 isFull(const mailbox* const mBox){
    return mBox->nMessages >= mBox->nMaxMessages;
}

b32 isEmpty(const mailbox* const mBox) {
    return mBox->pHead->pNext == mBox->pHead;
}

int no_messages(mailbox* mBox) {
    return mBox->nMessages;
}

b32 msgPushFront(mailbox* const mBox, msg* const m) {
    if (isFull(mBox)) { return 0; }
    
    mBox->nMessages++;
    insertMsg(m, getDummyMsg(mBox), getFirstMsg(mBox));
    
    return 1;
}

b32 msgPushBack(mailbox* const mBox, msg* const m) {
    if (isFull(mBox)) { return 0; }
    mBox->nMessages++;
    insertMsg(m, getLastMsg(mBox), getDummyMsg(mBox));
    
    return 1;
}

msg* msgPopFront(mailbox* const mBox) {
    if (isEmpty(mBox)) { return NULL; }
    mBox->nMessages--;
    //if (mBox->nBlockedMsg != 0) { mBox->nBlockedMsg--; }
    return removeMsg(getFirstMsg(mBox));
}

msg* msgPopBack(mailbox* const mBox) {
    if (isEmpty(mBox)) { return NULL; }
    mBox->nMessages--;
    //if (mBox->nBlockedMsg != 0) { mBox->nBlockedMsg--; }
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

exception remove_mailbox(mailbox* mBox) {
    if (!isEmpty(mBox)) { return NOT_EMPTY; }
    delete(mBox->pHead);
    delete(mBox);
    return OK;
}

b32 msgRecIsWaiting(const mailbox* const mBox) {
    return !isEmpty(mBox) && getFirstMsg(mBox)->Status == RECEIVER;
}

b32 msgSndIsWaiting(const mailbox* const mBox) {
    return !isEmpty(mBox) && getFirstMsg(mBox)->Status == SENDER;
}

exception send_wait(mailbox* mBox, void* pData) {
    volatile int first = TRUE;
    isr_off();
    SaveContext();
    
    if (first) {
        first = FALSE;
        if (msgRecIsWaiting(mBox)) {
            msg* rec = msgPopFront(mBox);
            memcpy(rec->pData, pData, getDataSize(mBox));
            rec->pBlock->pMessage = NULL;
            addTask_Deadline(readyList, removeTask(getTask(rec)));
            Running = getFirstTask(readyList)->pTask;
            delete(rec);
        } else {
            msg* new = createMsg(pData, getDataSize(mBox)); if (!new) { return FAIL; }
            new->Status = SENDER;
            new->pBlock = getFirstTask(readyList);
            getFirstTask(readyList)->pMessage = new;
            msgPushBack(mBox, new);
            mBox->nBlockedMsg++;
            addTask_Deadline(waitList, removeTask(getFirstTask(readyList)));
            Running = getFirstTask(readyList)->pTask;
        }
        
        LoadContext();
    } else {
        if (deadline() <= ticks()) {
            TaskNode* rTask ;
            isr_off();
            rTask = getFirstTask(readyList);
            delete(removeMsg(getTaskMsg(rTask)));
            rTask->pMessage = NULL;
            mBox->nBlockedMsg--;
            isr_on();
            return DEADLINE_REACHED;
        } else {
            return OK;
        }
    }
    return OK;
}

exception receive_wait(mailbox* mBox, void* pData) {
    volatile int first = TRUE;
    isr_off();
    SaveContext();
    
    if (first) {
        first = FALSE;
        if (msgSndIsWaiting(mBox)) {
            msg* snd = msgPopFront(mBox);
            memcpy(pData, snd->pData, getDataSize(mBox));
            
            if (snd->pBlock != NULL && mBox->nBlockedMsg != 0) {
                snd->pBlock->pMessage = NULL;
                addTask_Deadline(readyList, removeTask(snd->pBlock));
                Running = getFirstTask(readyList)->pTask;
                mBox->nBlockedMsg--;
            } else {
                delete(snd->pData);
            }
            delete(snd);
        } else {
            msg* new = createMsg(pData, getDataSize(mBox)); if (!new) { return FAIL; }
            new->Status = RECEIVER;
            new->pBlock = getFirstTask(readyList);
            getFirstTask(readyList)->pMessage = new;
            msgPushBack(mBox, new);
            addTask_Deadline(waitList, removeTask(getFirstTask(readyList)));
            Running = getFirstTask(readyList)->pTask;
            mBox->nBlockedMsg++;
        }
        LoadContext();
    } else {
        if (deadline() <= ticks()) {
            TaskNode* rTask ;
            isr_off();
            
            rTask = getFirstTask(readyList);
            delete(removeMsg(getTaskMsg(rTask)));
            rTask->pMessage = NULL;
            mBox->nBlockedMsg--;
            
            isr_on();
            return DEADLINE_REACHED;
        } else {
            return OK;
        }
    }
    return OK;
}

exception send_no_wait(mailbox* mBox, void* pData) {
    volatile int first = TRUE;
    isr_off();
    SaveContext();
    if (first) {
        first = FALSE;
        if (msgRecIsWaiting(mBox))  {
            msg* rec = msgPopFront(mBox);
            memcpy(rec->pData, pData, getDataSize(mBox));
            rec->pBlock->pMessage = NULL;
            addTask_Deadline(readyList, removeTask(getTask(rec)));
            Running = getFirstTask(readyList)->pTask;
            delete(rec);
        } else {
            msg* new    = alloc(sizeof *new);       if (!new)        { return FAIL; }
            new->pData  = alloc(getDataSize(mBox)); if (!new->pData) { return FAIL; }
            memcpy(new->pData, pData, mBox->nDataSize);
            new->Status = SENDER;
            new->pBlock = getFirstTask(readyList);
            getFirstTask(readyList)->pMessage = new;            
            if(isFull(mBox)) {
                delete(msgPopFront(mBox));
            }
            msgPushBack(mBox, new);
        }
        LoadContext();
    }
    return OK;
}

int receive_no_wait(mailbox* mBox, void* pData) {
    volatile int first = TRUE;
    isr_off();
    SaveContext();
    if (first) {
        first = FALSE;
        if (msgSndIsWaiting(mBox)) {
            msg* snd = msgPopFront(mBox);
            memcpy(pData, snd->pData, getDataSize(mBox));
            if (snd->pBlock != NULL && mBox->nBlockedMsg != 0) {
                snd->pBlock->pMessage = NULL;
                addTask_Deadline(readyList, removeTask(snd->pBlock));
                Running = getFirstTask(readyList)->pTask;
                mBox->nBlockedMsg--;
            } else {
                delete(snd->pData);
            }
            delete(snd);
        } else {
            return FAIL;
        }     
        LoadContext();
    }
    return OK;
}

