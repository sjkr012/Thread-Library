#if 0
 I have implemented the variable 'locked' as a flag
 so that i can lock and unlock my mutex.
 Also, i implemented to atomic_exchange to 1 until mutex is being used..
 no unbounded waiting was used in this mutex.c
 For this project, mutex are in unlocked status before initialization
 and only one thread is being accessed to mutex, i can just
 set up 'locked' status and just return for the sucess

#endif


#include <stdlib.h>
#include <syscall.h>
#include <simics.h>
#include <atomic.h>
/* P1 Specific includes */
#include <mutex_type.h>
#include <thread.h>
#include <thr_internals.h>
#include <assert.h>
#include <stdio.h>


// Uncomment the following line to disable printf calls
//#define _REMOVE_PRINTF_CALLS_
#ifdef _REMOVE_PRINTF_CALLS_
#define printf(...)
#endif // _REMOVE_PRINTF_CALLS_


int mutex_init(mutex_t* mutex)
{
    // if mutex is null then we fail to initialize
    if(mutex == NULL)
	return -1;

    // set the status 'locked' to 0
    mutex->locked = 0;

    return 0;
}

void mutex_destroy(mutex_t* mutex)
{
    // set the status 'locked' to -1 so that we can destroy mutex
    mutex->locked = -1;
    return;
}

void mutex_lock(mutex_t* mutex)
{
    // holding the status locked until it is used in another file or function
    while(atomic_exchange(&mutex->locked, 1) == 1) {
        // using syscall function 'yield' to proceed with next thread
	yield(-1);
    }
}

void mutex_unlock(mutex_t* mutex)
{
    // store 0 to locked status
    atomic_store(&mutex->locked, 0);
    return;
}
