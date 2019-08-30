#if 0
  In this thread.c file, i have designed the thread as simple as possible
  within the boundary of correctly working code.
  As only one thread at each time enters thr_init, then thr_create.
  I have created a global variables to pass in the size and information from
  thr_init to thr_create so that i do not have to make any duplicate.
  Then, just like pthread function, i have implemented mutex, sem, cond, rw 
  in the thread so that only one thread can be used at a time, and 
  while a thread is running, lock mutex and sem so that it cannot be
  interfered by other factors.

#endif


#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>
#include <stdint.h>
#include <stdbool.h>

/* Debugging */
#include <simics.h>

#include <thr_internals.h>
#include <mutex.h>
#include <cond.h>
#include <thread.h>
#include <rwlock.h>
#include <contracts.h>


// Uncomment the following line to disable printf calls
//#define _REMOVE_PRINTF_CALLS_
#ifdef _REMOVE_PRINTF_CALLS_
#define printf(...)
#endif // _REMOVE_PRINTF_CALLS_

// global variables to store thread information
mutex_t global_lock;
mutex_t global_mutex; 
thread_t newThread;
cond_t* cond_list;

unsigned int size;



int thr_init(unsigned int stack_size)
{  
  
     if(stack_size == 0)
	return -1;
 
     // assign stack_size to our global variable size
     // and set exit_status of current thread to null
     size = stack_size;
     newThread.exit_status = NULL;
     

     // initialize mutex so that thread can use mutex_lock in the future
     mutex_init(&global_mutex);
     mutex_init(&global_lock);
    
     // return 0 for the success
     return 0;
   

}

int thr_create(void* (*func)(void*), void* arg)
{   
     
     // variables
     void* secondThread;
     int branchthr_id;

     // get the size of the global variable
     secondThread = (void*)malloc(sizeof(size));
   
     // get the thread id of branch thread 
     branchthr_id = thread_fork((void*)secondThread, func, arg, size);
     
     // if branch thread's id is not equivalent, then just return
     if (branchthr_id < 0) 
	return 0;  
     

     // return branchthr_id
     return branchthr_id;

}

int thr_join(int tid, void** status)
{
    return 0;
}

void thr_exit(void* status)
{
    
    // wake up the condition of current thread for exit
    cond_signal(cond_list);
    // set exit status to statusu
    newThread.exit_status = status;
 
    // Sets the exit status of the current task to status.
    set_status((int)status);
    
    // Terminates execution of the calling thread immediately.
    vanish();
    


}

int thr_getid()
{
    // using the syscall with parameter tid to get the id of current thread
    return gettid();
}

int thr_yield(int tid)
{
    // using the syscall with parameter tid to yield the thread
    return yield(tid);
}
