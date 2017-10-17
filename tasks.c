#include "kernel_data.h"

// ================================= TASK NODE FUNCTIONS ========================== //

TCB* getTCB       (const TaskNode* const task)    { return task->pTask; }
uint getDeadline  (const TaskNode* const task)    { return getTCB(task)->DeadLine; }
uint getnTCnt     (const TaskNode* const task)    { return task->nTCnt; }
msg* getTaskMsg   (const TaskNode* const task)    { return task->pMessage; }

TaskNode* getNextTask(const TaskNode* const task) { return task->pNext; }
TaskNode* getPrevTask(const TaskNode* const task) { return task->pPrevious; }

TaskNode* allocTask(void (*body)(), uint d) {
    TaskNode* task = NULL;
    TCB*      tcb  = NULL;

    if (task = alloc(sizeof *task), !task)  { return NULL; }
    if (tcb  = alloc(sizeof *tcb),  !tcb)   { delete(task); return NULL; }

    tcb->DeadLine   = ticks() + d;
    tcb->PC         = body;
    tcb->SP         = &tcb->StackSeg[STACK_SIZE - 1];

    task->nTCnt     = ticks();
    task->pTask     = tcb;

    return task;
}

void deleteTask(TaskNode* tasks) {
    delete(tasks->pTask);
    delete(tasks);
}

void insertTask(TaskNode* const new, TaskNode* const prev, TaskNode* const next) {
    if (new && prev && next) {
        next->pPrevious = new;
        new->pNext      = next;
        new->pPrevious  = prev;
        prev->pNext     = new;
    }
}

TaskNode* removeTask(TaskNode* const task) {
    if (task) {
        TaskNode* const p   = task->pPrevious;
        TaskNode* const n   = task->pNext;
        p->pNext            = n;
        n->pPrevious        = p;
    }
    return task;
}

// ================================ TASK LIST FUNCTIONS ======================== //

TaskNode* getDummyTask (const TaskList* const tasks) { return tasks->pHead; }
TaskNode* getFirstTask (const TaskList* const tasks) { return getDummyTask(tasks)->pNext; }
TaskNode* getLastTask  (const TaskList* const tasks) { return getDummyTask(tasks)->pPrevious; }

TaskList* allocTaskList() {
    TaskList* taskList  = NULL;
    TaskNode* dummy     = NULL;

    if (taskList = alloc(sizeof *taskList), !taskList)  { return NULL; }
    if (dummy    = alloc(sizeof *dummy), !dummy)        { delete(taskList); return NULL; }

    dummy->pNext     = dummy;
    dummy->pPrevious = dummy;
    taskList->pHead  = dummy;
    taskList->pTail  = dummy;

    return taskList;
}
 
void addTask_Deadline(TaskList* const tasks, TaskNode* const new) {
    TaskNode* iter ;
    if (!new) { return; }

    iter = getFirstTask(tasks);

    while (iter != getDummyTask(tasks) && getDeadline(new) > getDeadline(iter)) {
        iter = getNextTask(iter);
    }

    insertTask(new, getPrevTask(iter), iter);
}

void addTask_nTCnt(TaskList* const tasks, TaskNode* const new) {
    TaskNode* iter ;
    if (!new) { return; }

    iter = getFirstTask(tasks); // NULL;

    while (iter != getDummyTask(tasks) && getnTCnt(new) > getnTCnt(iter)) {
        iter = getNextTask(iter);
    }

    insertTask(new, getPrevTask(iter), iter);
}

void printTaskList(const TaskList* const tasks) {
    TaskNode* iter = getFirstTask(tasks);

    while (iter != getDummyTask(tasks)) {
        printf("deadline: %d,\tnCTnt %d\n", getDeadline(iter), getnTCnt(iter));
        iter = getNextTask(iter);
    }
}

// ======================= Task Kernel Functions ======================== //

exception create_task(void (*body)(), uint d) {
    volatile int firstExec = 1;
    // allocate memory for TCB
    TaskNode* task = allocTask(body, d);
    if (task == NULL) { return FAIL; }
    
    // if start-up mode then
    if (kernelMode == INIT) {
        addTask_Deadline(readyList, task);
        return SUCCESS;
    } else  {
        // disable interrupts
        isr_off();

        SaveContext();
        if (firstExec) { // if first execution then
            firstExec = 0;

            addTask_Deadline(readyList, task);
            Running = getFirstTask(readyList)->pTask;

            LoadContext();
        }
    }
    return SUCCESS;
}

void terminate(void) {
    // Remove running task from Readylist
    deleteTask(removeTask(getFirstTask(readyList)));
    // Set next task to be the running task
    Running = getFirstTask(readyList)->pTask;

    LoadContext();
}

