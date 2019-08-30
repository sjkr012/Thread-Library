/** @file sem_type.h
 *  @brief This file defines the type for semaphores.
 */


#ifndef _SEM_TYPE_H
#define _SEM_TYPE_H


#include <mutex_type.h>

typedef struct sem_s {
    int count;
    int w_count;


} sem_t;

#endif /* _SEM_TYPE_H */
