#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include "kernel.h"
#include "kernel_data.h"


mailbox* create_mailbox(uint nMessages, uint nDataSize)
{
    mailbox* mb = calloc(1, sizeof(mailbox));
    mb->nMaxMessages = nMessages;
    mb->nDataSize = nDataSize;
    return mb;
}

int no_messages(mailbox* mBox)
{
    if(mBox->nMessages == 0)
    {
        free(mBox);
        return OK;
    }
    return NOT_EMPTY;
}

exception send_wait(mailbox* mBox, void* pData)
{
    volatile int isFirst = TRUE;
    // Disable interrupt
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
            // Disable interrupt
            // Remove send Message
            // Enable interrupt
            return DEADLINE_REACHED;
        } else
        {
            return OK;
        }
    }
    //return SUCCESS;
}

exception receive_wait(mailbox* mBox, void* pData)
{
    volatile int isFirst = TRUE;
    // Disable interrupt
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
            // Disable interrupt
            // Remove receive Message
            // Enable interrupt
            return DEADLINE_REACHED;
        } else
        {
            return OK;
        }
    }
    //return SUCCESS;
}

exception send_no_wait(mailbox* mBox, void* pData)
{
    volatile int isFirst = TRUE;
    // Disable interrupt
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

int receive_no_wait(mailbox* mBox, void* pData)
{
    volatile int isFirst = TRUE;
    // Disable interrupt
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