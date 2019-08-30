/** @file rwlock_type.h
 *  @brief This file defines the type for reader/writer locks.
 */



#ifndef _RWLOCK_TYPE_H
#define _RWLOCK_TYPE_H

#include <mutex_type.h>
#include <cond_type.h>
#include <stdbool.h>


typedef struct rwlock_s {
    /* IMPLEMENT THIS */

    mutex_t m;
    cond_t cv;
    int count;
    bool writer_locked;

} rwlock_t;

#endif /* _RWLOCK_TYPE_H */
