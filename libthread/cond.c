#if 0

  for conditional variables, i have implemented in really simple way.
  just like other c file, i have set a count variable as a count of conditional variables
  to be used in other function. 
  With this count flag, i set 0 for the init, -1 for the destroy
  and for cond_wait, cond_signal, cond_broadcast, i have implemented
  syscall wrappers make_runnable, and wait so that whenever each function is called,
  it can act as a syscall wrappers.


#endif 


#include <stdlib.h>
#include <syscall.h>
#include <atomic.h>
#include <cond_type.h>
#include <mutex_type.h>
#include <mutex.h>
#include <thread.h>
#include <simics.h>
#include <thr_internals.h>


// Uncomment the following line to disable printf calls
//#define _REMOVE_PRINTF_CALLS_
#ifdef _REMOVE_PRINTF_CALLS_
#define printf(...)
#endif // _REMOVE_PRINTF_CALLS_

int cond_init(cond_t* cond)
{
  // set initial count to 0
  cond->count = 0;
  return 0;
 

}

void cond_destroy(cond_t* cond)
{
    // set count to be -1 so that condition can be destroyed
    cond->count = -1;
    return;
}

void cond_wait(cond_t* cond, mutex_t* mutex)
{
    mutex_lock(mutex);
    // decrement number of count, decrement waiting count
    
    atomic_fetch_add(&cond->w_count, 1);

    // use wait function to pause(wait) currently running mutex
    wait(&mutex->locked);
  
    atomic_fetch_sub(&cond->count, 1);
 
    mutex_unlock(mutex);

    return;


}

void cond_signal(cond_t* cond)
{
    
    // increment number of count, decrement number of waiting counts
    atomic_fetch_sub(&cond->w_count, 1);
    atomic_fetch_add(&cond->count, 1);
    
 
    // wakes up the current thread
    make_runnable(cond->count);
}

void cond_broadcast(cond_t* cond)
{
    // unlike signal, broadcast wakes all thread, so i didn't
    // decrement / increment any counts
    make_runnable(cond->count);

}
