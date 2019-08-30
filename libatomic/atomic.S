/* int atomic_exchange(volatile int* obj, int desired); */
    .global atomic_exchange
atomic_exchange:
    /* IMPLEMENT THIS */
    push %ebx
    mov 0x8(%esp), %edx  //obj
    mov 0xc(%esp), %ebx  //desired
    mov (%edx), %ecx     //old_val = *obj;
    mov %ebx, (%edx)     //*obj = desired
    mov %ecx, %eax       // return old_val
    pop %ebx
    ret

/* int atomic_compare_swap(volatile int* obj, int expected, int desired); */
    .global atomic_compare_swap
atomic_compare_swap:
    /* IMPLEMENT THIS */
    push %ebx
    mov 0x8(%esp), %edx // obj
    mov 0xc(%esp), %ebx // expected
    mov 0x10(%esp), %eax // desired
    mov (%edx), %ecx  // old_val = *obj;
    cmp %ecx, %ebx    // if (old_val == expected)
    je match          // jump to matchs
    mov %ecx, %eax    // return old_val
    pop %ebx
    ret

match:
    mov %eax, (%edx)   // *obj = desired
    mov %ecx, %eax     // return old_val
    pop %ebx
    ret

/* int atomic_fetch_add(volatile int* obj, int arg); */
    .global atomic_fetch_add
atomic_fetch_add:
    /* IMPLEMENT THIS */
    push %ebx
    mov 0x8(%esp), %edx  // obj
    mov 0xc(%esp), %ebx  // arg
    mov (%edx), %ecx     // old_val = *obj;
    add %ebx, (%edx)     // *obj += arg;
    mov %ecx, %eax       // return old_val
    pop %ebx
    ret

/* int atomic_fetch_sub(volatile int* obj, int arg); */
    .global atomic_fetch_sub
atomic_fetch_sub:
    /* IMPLEMENT THIS */
    push %ebx
    mov 0x8(%esp), %edx  // obj
    mov 0xc(%esp), %ebx  // arg
    mov (%edx), %ecx     // old_val = *obj;
    sub %ebx, (%edx)     // *obj -= arg;
    mov %ecx, %eax       // return old_val
    pop %ebx
    ret

/* int atomic_load(volatile int* obj); */
    .global atomic_load
atomic_load:
    /* IMPLEMENT THIS */
    push %ebx
    mov 0x8(%esp), %ebx // obj
    mov (%ebx), %eax    // load and return value of memory location of obj
    pop %ebx
    ret

/* void atomic_store(volatile int* obj, int desired); */
    .global atomic_store
atomic_store:
    /* IMPLEMENT THIS */
    push %ebx
    mov 0x8(%esp), %edx // obj
    mov 0xc(%esp), %ebx // desired
    mov %ebx, (%edx)    // store desired to memory location of obj
    pop %ebx
    ret
