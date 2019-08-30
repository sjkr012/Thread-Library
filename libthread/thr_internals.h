/** @file thr_internals.h
 *  
 * 
 *  @brief This file may be used to define things
 *         internal to the thread library.
 */
#ifndef THR_INTERNALS_H
#define THR_INTERNALS_H


#include <stdbool.h>
#include <mutex_type.h>
#include <cond_type.h>
#include <rwlock_type.h>

#define THR_STATUS_DEAD 1
/** @brief Denotes a thread has exited but has not been joined on */
#define THR_STATUS_ZOMBIE 2
/** @brief Denotes a thread is currently running or sleeping */
#define THR_STATUS_ALIVE 0


typedef struct {

     void* exit_status;   // represent exit_status of each thread created
 
} thread_t;


#endif /* THR_INTERNALS_H */
