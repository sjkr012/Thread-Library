#if 0
  i have implemented semaphore with the count, waiting count variable to
  remember how many data are waiting in semaphore and how many of them can
  be used in semaphore.


#endif 

#include <sem.h>
#include <atomic.h>
#include <syscall.h>
#include <mutex.h>
#include <thr_internals.h>
#include <syscall.h>

// Uncomment the following line to disable printf calls
//#define _REMOVE_PRINTF_CALLS_
#ifdef _REMOVE_PRINTF_CALLS_
#define printf(...)
#endif // _REMOVE_PRINTF_CALLS_

int sem_init(sem_t* sem, int count)
{
    // if parameter count is less than 0, it fails
    if(count < 0)
	return -1;
    else
        sem->count = count;
    // store parameter count to current semaphore's count
     

    return 0;

}

void sem_destroy(sem_t* sem)
{
    // if there is no semaphore, then just return
    if(sem == 0) 
       return;
    else
       sem->count = -1;

}

void sem_wait(sem_t* sem)
{
    // if there is no semaphore, then just return
    if(sem == 0)
	return;

    //increment waiting count
    atomic_fetch_add(&sem->w_count, 1);
   
    // if there is no data available, wait until we find and yield
    while (atomic_load(&sem->count) <= 0)
    {
	yield(-1);
    }
    
    // decrement count
    atomic_fetch_sub(&sem->count, 1);

    return;
}

void sem_signal(sem_t* sem)
{
    // decrement waiting count
    atomic_fetch_sub(&sem->w_count, 1);
   
    // wakes up all semaphores in used 
    make_runnable(sem->count);

    // increment count
    atomic_fetch_add(&sem->count, 1);

}
