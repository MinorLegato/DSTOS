#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include "kernel.h"
#include "kernel_data.h"


mailbox* create_mailbox(uint nMessages, uint nDataSize)
{
    // Allocate memory for the Mailbox
    // Initialize Mailbox structure
    // Return Mailbox*
    return NULL;
}

int no_messages(mailbox* mBox)
{
    // IF Mailbox is empty THEN
    // Free the memory for the Mailbox
    // Return OK
    // ELSE
    // Return NOT_EMPTY
    // ENDIF
    return 0;
}

exception send_wait(mailbox* mBox, void* pData)
{
    // Disable interrupt
    // Save context
    // IF first execution THEN
    // Set: �not first execution any more�
    // IF receiving task is waiting THEN
    // Copy sender�s data to the data area
    // of the receivers Message
    // Remove receiving task�s Message
    // struct from the mailbox
    // Move receiving task to Readylist
    // ELSE
    // Allocate a Message structure
    // Set data pointer
    // Add Message to the Mailbox
    // Move sending task from Readylist to
    // Waitinglist
    // ENDIF
    // Load context
    // ELSE
    // IF deadline is reached THEN
    // Disable interrupt
    // Remove send Message
    // Enable interrupt
    // Return DEADLINE_REACHED
    // ELSE
    // Return OK
    // ENDIF
    // ENDIF
    return SUCCESS;
}

exception receive_wait(mailbox* mBox, void* pData)
{
    // Disable interrupt
    // Save context
    // IF first execution THEN
    // Set: �not first execution any more�
    // IF send Message is waiting THEN
    // Copy sender�s data to receiving task�s
    // data area
    // Remove sending task�s Message
    // struct from the Mailbox
    // IF Message was of wait type THEN
    // Move sending task to Ready list
    // ELSE
    // Free senders data area
    // ENDIF
    // ELSE
    // Allocate a Message structure
    // Add Message to the Mailbox
    // Move receiving task from Readylist to
    // Waitinglist
    // ENDIF
    // Load context
    // ELSE
    // IF deadline is reached THEN
    // Disable interrupt
    // Remove receive Message
    // Enable interrupt
    // Return DEADLINE_REACHED
    // ELSE
    // Return OK
    // ENDIF
    // ENDIF
    return SUCCESS;
}

exception send_no_wait(mailbox* mBox, void* pData)
{
    // Disable interrupt
    SaveContext();
    // IF first execution THEN
    if (0) {
        // Set: �not first execution anymore�
        // IF receiving task is waiting THEN
        if (0) {
            // Copy data to receiving tasks�
            // data area.
            // Remove receiving task�s Message
            // struct from the Mailbox
            // Move receiving task to Readylist
            // Load context
        } else {
            // Allocate a Message structure
            // Copy Data to the Message
            // IF mailbox is full THEN
            if (0) {
                // Remove the oldest Message struct
            }
            // Add Message to the Mailbox
        }
    }
    return SUCCESS;
}

int receive_no_wait(mailbox* mBox, void* pData)
{
    // Disable interrupt
    SaveContext();
    // IF first execution THEN
    if (0) {
        // Set: �not first execution any more�
        // IF send Message is waiting THEN
        if (0) {
            // Copy sender�s data to receiving task�s
            // data area
            // Remove sending task�s Message
            // struct from the Mailbox
            // IF Message was of wait type THEN
            if (0) {
                // Move sending task to Readylist
            }        
            else {
                // Free sender�s data area
            }       
        }
        LoadContext();
    }
    // Return status on received Message
    return 0;
}


#endif

