/** @file cond_type.h
 *  @brief This file defines the type for condition variables.
 */



#ifndef _COND_TYPE_H
#define _COND_TYPE_H

#include <mutex_type.h>

typedef struct cond_t {

    int count;
    int w_count;


} cond_t;

#endif /* _COND_TYPE_H */
