#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include "kernel.h"
#include "kernel_data.h"

// Creates a new mailbox
mailbox* create_mailbox(uint nMessages, uint nDataSize) {
    mailbox* mb = alloc(sizeof(mailbox));
    msg* head = alloc(sizeof(msg));
    msg* tail = alloc(sizeof(msg));
    
    head->pNext = tail;
    head->pPrevious = NULL;
    
    tail->pNext = NULL;
    tail->pPrevious = head;
    
    mb->pHead = head;
    mb->pTail = tail;
    mb->nMaxMessages = nMessages;
    mb->nDataSize = nDataSize;
    mb->nMessages = 0;
    mb->nBlockedMsg = 0;
    return mb;
}

static int isEmpty(mailbox* mBox) { return mBox->pHead->pNext == mBox->pTail; }
static int isFull(mailbox* mBox)  { return mBox->nMessages == mBox->nMaxMessages; }

exception remove_mailbox(mailbox* mBox) {
    return isEmpty(mBox)? delete(mBox), OK : NOT_EMPTY;
}

// Removes a mailbox if it's empty
int no_messages(mailbox* mBox) {
    if(isEmpty(mBox)) {
        delete(mBox->pHead);
        delete(mBox->pTail);
        delete(mBox);
        return OK;
    }
    return NOT_EMPTY;
}

// Deletes a mailbox and all its content
int delete_mailbox(mailbox* mBox) {
    while(!no_messages(mBox)) {
        if(mBox->nMessages == 0) {
            return FAIL;
        }
        msg* temp = mBox->pHead->pNext;
        mBox->pHead->pNext = mBox->pHead->pNext->pNext;
        mBox->pHead->pNext->pPrevious = mBox->pHead;
        mBox->nMessages--;
        delete(temp);
    }
    return OK;
}

// Keeps the mailbox but deletes all its content
int clear_mailbox(mailbox* mBox) {
    while(!isEmpty(mBox)) {
        msg* temp = mBox->pHead->pNext;
        mBox->pHead->pNext = mBox->pHead->pNext->pNext;
        mBox->pHead->pNext->pPrevious = mBox->pHead;
        mBox->nMessages--;
        delete(temp);
    }
    return OK;
}

// Deletes last message in a mailbox
int delete_msg_last(mailbox* mBox) {
    if(!isEmpty(mBox)) {
        msg* temp = mBox->pTail->pPrevious;
        temp->pPrevious->pNext = temp->pNext;
        temp->pNext->pPrevious = temp->pPrevious;
        mBox->nMessages--;
        delete(temp);
        return OK;
    }
    return FAIL;
}

// Deletes a message from a mailbox
int delete_msg(mailbox* mBox, msg* Message) {
    if(!isEmpty(mBox)) {
        msg* temp = mBox->pHead->pNext;
        while(temp != mBox->pTail) {
            if(temp == Message) {
                temp->pPrevious->pNext = temp->pNext;
                temp->pNext->pPrevious = temp->pPrevious;
                mBox->nMessages--;
                delete(temp);
                return OK;
            }
            temp->pNext = temp->pNext->pNext;
        }
    }
    return FAIL;
}

// Deletes a message from a mailbox based on the data in the message
int delete_data(mailbox* mBox, void* pData) {
    if(!isEmpty(mBox)) {
        msg* temp = mBox->pHead->pNext;
        char data = *(char*)pData;
        while(temp != mBox->pTail) {
            if(*temp->pData == data) {
                temp->pPrevious->pNext = temp->pNext;
                temp->pNext->pPrevious = temp->pPrevious;
                mBox->nMessages--;
                delete(temp);
                return OK;
            }
            temp->pNext = temp->pNext->pNext;
        }
    }
    return FAIL;
}

//Allocates a msg
msg* alloc_msg(void* pData) {
    msg* Message = alloc(sizeof(msg));
    if(Message != NULL) {
        Message->pData = pData;
    }
    return Message;
}

// Adds message first in mailbox
exception add_msg_first(mailbox* mBox, msg* Message) {
    if(!isFull(mBox)) {
        if(Message != NULL) {
            Message->pNext = mBox->pHead->pNext;
            mBox->pHead->pNext = Message;
            mBox->nMessages++;
            return OK;
        }
    }
    return FAIL;
}

// Adds message last in mailbox
exception add_msg_last(mailbox* mBox, msg* Message) {
    if(!isFull(mBox)) {
        if(Message != NULL) {
            Message->pNext = mBox->pTail;
            mBox->pTail->pPrevious->pNext = Message;
            mBox->nMessages++;
            return OK;
        }
    }
    return FAIL;
}

// Creates new message first in mailbox
exception create_msg_first(mailbox* mBox, void* pData) {
    msg* Message = alloc_msg(pData);
    if(Message != NULL) {
        add_msg_first(mBox, Message);
        return OK;
    }
    return FAIL;
}

// Creates new message last in mailbox
exception create_msg_last(mailbox* mBox, void* pData) {
    msg* Message = alloc_msg(pData);
    if(Message != NULL) {
        add_msg_last(mBox, Message);
        return OK;
    }
    return FAIL;
}

// NOTE: TEST!!
exception send_wait(mailbox* mBox, void* pData) {
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if(isFirst) {
        isFirst = FALSE;
        // IF receiving task is waiting THEN
        if(mBox->pHead->Status == RECEIVER) {
            // Copy senderís data to the data area of the receivers Message
            memcpy(mBox->pHead->pData, pData, sizeof (mBox->nDataSize));
            // Remove receiving task's Message struct from the mailbox;
            TaskNode* task = mBox->pHead->pBlock;
            delete_msg(mBox, mBox->pHead);
            // Move receiving task to Readylist
            addTask_Deadline(&readyList, removeTask(task));
        } else {
            create_msg_first(mBox, pData);
            // Move sending task from Readylist to Waitinglist
            addTask_Deadline(&waitList, removeTask(mBox->pHead->pBlock));
        }
        LoadContext();
    } else {
        // IF deadline is reached THEN
        if(mBox->pHead->pBlock->pTask.Deadline) {
            //isr_off();
            // Remove send Message
            delete_msg(mBox, mBox->pHead);
            //isr_on();
            return DEADLINE_REACHED;
        }
    }
    return OK;
}

// NOTE: TEST!!
exception receive_wait(mailbox* mBox, void* pData) {
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if(isFirst) { 
        isFirst = FALSE;
        // IF send Message is waiting THEN
        if(mBox->pHead->Status == SENDER) {
            // Copy sender's data to receiving task's data area
            memcpy(pData, mBox->pHead, mBox->pDataSize);
            // Remove sending task's Message struct from the Mailbox
            TaskNode* task = mBox->pHead->pBlock;
            delete_msg(mBox, mBox->pHead);
            // IF Message was of wait type THEN
            if (m->Status == 0) {
                // Move sending task to Ready list
            } else {
                // Free senders data area
                delete(mBox->pHead->pData);
            }
        } else {
            // Allocate a Message structure
            msg* m = alloc_msg(pData);
            m->pTask = mBox->pHead->pTask;
            // Add Message to the Mailbox
            add_msg_first(mBox, m);
            // Move receiving task from Readylist to Waitinglist
            addTask_Deadline(&waitList, removeTask(readyList, m->pTask));
        }
        LoadContext();
    } else {
        // IF deadline is reached THEN
        if (mBox->pHead->pTask.DeadLine == 0) {
            //isr_off();
            delete_msg(mBox, mBox->pHead);
            //isr_on();
            return DEADLINE_REACHED;
        } 
    }
    return OK;
}

// NOTE: TEST!!
exception send_no_wait(mailbox* mBox, void* pData) {
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if (isFirst) {
        isFirst = FALSE;
        // IF receiving task is waiting THEN
        if (0)  {
            // Copy data to receiving tasksí
            // data area.
            // Remove receiving taskís Message
            // struct from the Mailbox
            // Move receiving task to Readylist
            LoadContext();
        } else {
            if(isFull(mBox)) {
                delete_msg_last(mBox);
            }
            create_msg_first(mBox, pData);
        }
    }
    return OK;
}

// NOTE: TEST!!
int receive_no_wait(mailbox* mBox, void* pData) {
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if (isFirst)  {
        isFirst = FALSE;
        // IF send Message is waiting THEN
        if (0) {
            // Copy senderís data to receiving taskís
            // data area
            // Remove sending taskís Message
            // struct from the Mailbox
            // IF Message was of wait type THEN
            if (0) {
                // Move sending task to Readylist
            } else  {
                // Free senderís data area
            }       
        }
        LoadContext();
    }
    return OK;
}

#endif
