#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include "kernel.h"
#include "kernel_data.h"


// Creates a new mailbox
mailbox* create_mailbox(uint nMessages, uint nDataSize)
{
    mailbox* mb = calloc(1, sizeof(mailbox));
    msg* head = calloc(1, sizeof(msg));
    msg* tail = calloc(1, sizeof(msg));
    head->pNext = tail;
    head->pPrevious = NULL;
    tail->pNext = NULL;
    tail->pPrevious = head;
    mb->pHead = head;
    mb->pTail = tail;
    mb->nMaxMessages = nMessages;
    mb->nDataSize = nDataSize;
    return mb;
}


// Removes a mailbox if it's empty
int no_messages(mailbox* mBox)
{
    if(mBox->pHead->pNext == mBox->pTail)
    {
        free(mBox->pHead);
        free(mBox->pTail);
        free(mBox);
        return OK;
    }
    return NOT_EMPTY;
}


// Deletes all content of a mailbox
int delete_mailbox(mailbox* mBox)
{
    while(!no_messages(mBox)) {
        if(mBox->nMessages == 0) {
            return FAIL;
        }

        msg* temp = mBox->pHead->pNext;
        mBox->pHead->pNext = mBox->pHead->pNext->pNext;
        mBox->pHead->pNext->pPrevious = mBox->pHead;
        mBox->nMessages--;

        free(temp);
    }
    return OK;
}


//Allocates a msg
msg* alloc_msg(void* pData)
{
    msg* Message = calloc(1, sizeof(msg));
    if(Message != NULL)
    {
        Message->pData = pData;
    }
    return Message;
}


// Adds message first in mailbox
exception add_msg_first(mailbox* mBox, msg* Message)
{
    if(Message != NULL)
    {
        Message->pNext = mBox->pHead->pNext;
        mBox->pHead->pNext = Message;
        mBox->nMessages++;
        return OK;
    }
    return FAIL;
}


// Adds message last in mailbox
exception add_msg_last(mailbox* mBox, msg* Message)
{
    if(Message != NULL)
    {
        Message->pNext = mBox->pTail;
        mBox->pTail->pPrevious->pNext = Message;
        mBox->nMessages++;
        return OK;
    }
    return FAIL;
}


// Creates new message first in mailbox
exception create_msg_first(mailbox* mBox, void* pData)
{
    msg* Message = alloc_msg(pData);
    if(Message != NULL)
    {
        add_msg_first(mBox, Message);
        return OK;
    }
    return FAIL;
}


// Creates new message last in mailbox
exception create_msg_last(mailbox* mBox, void* pData)
{
    msg* Message = alloc_msg(pData);
    if(Message != NULL)
    {
        add_msg_last(mBox, Message);
        return OK;
    }
    return FAIL;
}


// Send ....
exception send_wait(mailbox* mBox, void* pData)
{
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if(isFirst)
    {
        isFirst = FALSE;
        // IF receiving task is waiting THEN
        if(0)
        {
            // Copy senderís data to the data area
            // of the receivers Message
            // Remove receiving taskís Message
            // struct from the mailbox
            // Move receiving task to Readylist
        } else
        {
            // Allocate a Message structure
            // Set data pointer
            // Add Message to the Mailbox
            // Move sending task from Readylist to
            // Waitinglist
        }
        LoadContext();
    } else
    {
        // IF deadline is reached THEN
        if(0)
        {
            isr_off();
            // Remove send Message
            isr_on();
            return DEADLINE_REACHED;
        }
    }
    return OK;
}


// Receive ....
exception receive_wait(mailbox* mBox, void* pData)
{
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if(isFirst)
    {   
        isFirst = FALSE;
        // IF send Message is waiting THEN
        if(0)
        {
            // Copy senderís data to receiving taskís
            // data area
            // Remove sending taskís Message
            // struct from the Mailbox
            // IF Message was of wait type THEN
            if(0)
            {
                // Move sending task to Ready list
            } else
            {
                // Free senders data area
            }
        } else
        {
            // Allocate a Message structure
            // Add Message to the Mailbox
            // Move receiving task from Readylist to
            // Waitinglist
        }
        LoadContext();
    } else
    {
        // IF deadline is reached THEN
        if(0)
        {
            isr_off();
            // Remove receive Message
            isr_on();
            return DEADLINE_REACHED;
        } 
    }
    return OK;
}


// Send ....
exception send_no_wait(mailbox* mBox, void* pData)
{
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if (isFirst) 
    {
        isFirst = FALSE;
        // IF receiving task is waiting THEN
        if (0) 
        {
            // Copy data to receiving tasksí
            // data area.
            // Remove receiving taskís Message
            // struct from the Mailbox
            // Move receiving task to Readylist
            LoadContext();
        } else 
        {
            // Allocate a Message structure
            // Copy Data to the Message
            // IF mailbox is full THEN
            if (0) 
            {
                // Remove the oldest Message struct
            }
            // Add Message to the Mailbox
        }
    }
    return OK;
}


// Receive ....
int receive_no_wait(mailbox* mBox, void* pData)
{
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if (isFirst) 
    {
        isFirst = FALSE;
        // IF send Message is waiting THEN
        if (0) 
        {
            // Copy senderís data to receiving taskís
            // data area
            // Remove sending taskís Message
            // struct from the Mailbox
            // IF Message was of wait type THEN
            if (0) 
            {
                // Move sending task to Readylist
            } else 
            {
                // Free senderís data area
            }       
        }
        LoadContext();
    }
    return OK;
}


#endif
