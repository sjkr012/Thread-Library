#if 0
   to make our malloc functions thread-safe,
   i have simply implemented mutex locks & unlocks
   so only one thread can be accessed at a time.

#endif


#include <malloc.h>
#include <stdlib.h>
#include <types.h>
#include <stddef.h>

// Uncomment the following line to disable printf calls
//#define _REMOVE_PRINTF_CALLS_
#ifdef _REMOVE_PRINTF_CALLS_
#define printf(...)
#endif // _REMOVE_PRINTF_CALLS_

#include <stdlib.h>
#include <mutex.h>
#include <thr_internals.h>

mutex_t mutex;

void* malloc(size_t size)
{
    // mutex_lock the current thread
    mutex_lock(&mutex);

    // assign malloc function to new void variable inside locks
    void *thr_safe_malloc = _malloc(size);
    
    // mutex_unlock after malloc finished
    mutex_unlock(&mutex);

    return thr_safe_malloc;
}

void* calloc(size_t nelt, size_t eltsize)
{
    // mutex_lock the current thread
    mutex_lock(&mutex);

    // assign calloc function to new void variable inside locks
    void *thr_safe_calloc = _calloc(nelt, eltsize);

    // mutex_unlock after calloc finished
    mutex_unlock(&mutex);

    return thr_safe_calloc;

}

void* realloc(void* buf, size_t new_size)
{
    // mutex_lock the current thread
    mutex_lock(&mutex);
  
    // assign realloc function to new void variable inside locks
    void *thr_safe_realloc = _realloc(buf, new_size);

    // mutex_unlock after realloc finished
    mutex_unlock(&mutex);

    return thr_safe_realloc;

}

void free(void* buf)
{
    // mutex_lock the current thread
    mutex_lock(&mutex);
    // assign free function to new void variable inside locks
    _free(buf);
    // mutex_unlock after free
    mutex_unlock(&mutex);
}
