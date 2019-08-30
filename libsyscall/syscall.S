#include <syscall_int.h>

/* int fork(void); */
    .global fork
fork:
    push %esi
    mov 0x8(%esp), %esi
    mov 0xc(%esp), %esi
    int $0x41
    pop %esi    
    ret

/* int thread_fork(void *sp, void *(*func)(void*), void *args, int size); */
    .globl thread_fork
thread_fork:
	mov 0x4(%esp), %ecx
        add 0x10(%esp), %ecx
        mov 0xc(%esp), %edx
        push %ebx
        mov 0xc(%esp), %ebx

        int $0x52
 
        cmp $0, %eax
        je nextthr_fork
        pop %ebx
        ret

nextthr_fork:
	mov %ecx, %esp
        push %edx
        call *%ebx
        push %eax
        call *thr_exit




/* int exec(char* execname, char* argvec[]); */
    .global exec
exec:
    push %esi
    lea 0x8(%esp), %esi
    int $0x42
    pop %esi
    ret

/* void set_status(int status); */
    .global set_status
set_status:
    /* IMPLEMENT THIS */
    push %esi
    mov 0x8(%esp), %esi 
    int $0x59
    pop %esi
    ret

/* void vanish(void) NORETURN; */
    .global vanish
vanish:
    /* IMPLEMENT THIS */
    push %esi
    mov 0x8(%esp), %esi
    int $0x60
    pop %esi
    ret

/* int wait(int* status_ptr); */
    .global wait
wait:
    push %esi
    mov 0x8(%esp), %esi
    int $0x44
    pop %esi
    ret

/* void task_vanish(int status) NORETURN; */
    .global task_vanish
task_vanish:
    push %esi
    mov 0x8(%esp), %esi
    int $0x57
    pop %esi
    ret

/* int gettid(void); */
    .global gettid
gettid:
    /* IMPLEMENT THIS */
    push %esi
    lea 0x8(%esp), %esi
    int $0x48
    pop %esi
    ret

/* int yield(int pid); */
    .global yield
yield:
    push %esi
    mov 0x8(%esp), %esi
    int $0x45
    pop %esi
    ret

/* int deschedule(int* flag); */
    .global deschedule  
deschedule:
    push %esi
    mov 0x8(%esp), %esi
    int $0x46
    pop %esi
    ret

/* int make_runnable(int pid); */
    .global make_runnable 
make_runnable:          
    push %esi
    mov 0x8(%esp), %esi
    int $0x47
    pop %esi
    ret

/* unsigned int get_ticks(void); */
    .global get_ticks
get_ticks:
    push %esi
    mov 0x8(%esp), %esi
    int $0x53
    pop %esi
    ret

/* int sleep(int ticks); */
    .global sleep
sleep:
    push %esi
    mov 0x8(%esp), %esi
    int $0x4B
    pop %esi
    ret

/* int new_pages(void* addr, int len); */
    .global new_pages
new_pages:
    push %esi
    lea 0x8(%esp), %esi
    int $0x49
    pop %esi
    ret

/* int remove_pages(void* addr); */
    .global remove_pages
remove_pages:
    push %esi
    mov 0x8(%esp), %esi
    int $0x4A
    pop %esi
    ret

/* int getchar(void); */
    .global getchar
getchar:
    push %esi
    mov 0x8(%esp), %esi
    int $0x4C
    pop %esi
    ret

/* int readline(int size, char* buf); */
    .global readline 
readline:
    push %esi
    lea 0x8(%esp), %esi
    int $0x62
    pop %esi
    ret

/* int print(int size, char* buf); */
    .global print
print:
    push %esi
    lea 0x8(%esp), %esi
    int $0x4E
    pop %esi
    ret

/* int set_term_color(int color); */
    .global set_term_color
set_term_color:
    push %esi
    mov 0x8(%esp), %esi
    int $0x4F
    pop %esi
    ret

/* int set_cursor_pos(int row, int col); */
    .global set_cursor_pos
set_cursor_pos:
    /* IMPLEMENT THIS */
    push %esi
    lea 0x8(%esp), %esi
    int $0x50
    pop %esi
    ret

/* int get_cursor_pos(int* row, int* col); */
    .global get_cursor_pos
get_cursor_pos:
    push %esi
    lea 0x8(%esp), %esi
    int $0x51
    pop %esi
    ret

/* void halt(); */
    .global halt 
halt:
    int $0x55

    ret

/* int readfile(char* filename, char* buf, int count, int offset); */
    .global readfile
readfile:
    push %esi
    lea 0x8(%esp), %esi
    int $0x62
    pop %esi
    ret

/* void misbehave(int mode); */
    .global misbehave
misbehave:
    push %esi
    lea 0x8(%esp), %esi
    int $0x54
    pop %esi
    ret

/* int swexn(void* esp3, swexn_handler_t eip, void* arg, ureg_t* newureg); */
    .global swexn
swexn:
    push %esi
    lea 0x8(%esp), %esi
    int $0x74
    pop %esi
    ret

