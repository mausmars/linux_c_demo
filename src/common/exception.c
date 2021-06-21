#include "exception.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

Exception_frame *Exception_stack = NULL;

void exception_raise(const Exception_t *e, const char *file, int line) {
    Exception_frame *p = Exception_stack;
    assert(e);
    if (p == NULL) {
        abort_without_exception(e, file, line);
    }
    p->exception = e;
    p->file = file;
    p->line = line;
    Exception_stack = Exception_stack->prev;
    longjmp(p->env, EXCEPTION_RAISED);
}

void abort_without_exception(const Exception_t *e, const char *file, int line) {
    //fprintf(stderr,"Uncaught exception");
    if (e->reason) {
        fprintf(stderr, " %s", e->reason);
    } else {
        fprintf(stderr, "at 0x%p", e);
    }
    if (file && line > 0) {
        fprintf(stderr, "raised at %s:%d\n", file, line);
    }
    fprintf(stderr, "aborting...\n");
    fflush(stderr);
    abort();
}

void handle_proc_sig(int signo) {
    if (signo == MANPROCSIG_HUP)
        printf(" Hangup (POSIX). \r\n");
    else if (signo == MANPROCSIG_INT)
        printf(" Interrupt (ANSI). \r\n");
    else if (signo == MANPROCSIG_QUIT)
        printf(" Quit (POSIX). \r\n");
    else if (signo == MANPROCSIG_ILL)
        printf(" Illegal instruction (ANSI). \r\n");
    else if (signo == MANPROCSIG_TRAP)
        printf(" Trace trap (POSIX). \r\n");
    else if (signo == MANPROCSIG_ABRT)
        printf(" Abort (ANSI). \r\n");
    else if (signo == MANPROCSIG_IOT)
        printf(" IOT trap (4.2 BSD). \r\n");
    else if (signo == MANPROCSIG_BUS)
        printf(" BUS error (4.2 BSD). \r\n");
    else if (signo == MANPROCSIG_FPE)
        printf(" Floating-point exception (ANSI). \r\n");
    else if (signo == MANPROCSIG_KILL)
        printf(" Kill, unblockable (POSIX). \r\n");
    else if (signo == MANPROCSIG_USR1)
        printf(" User-defined signal if( signo == (POSIX). \r\n");
    else if (signo == MANPROCSIG_SEGV)
        printf(" Segmentation violation (ANSI). \r\n");
    else if (signo == MANPROCSIG_USR2)
        printf(" User-defined signal 2 (POSIX). \r\n");
    else if (signo == MANPROCSIG_PIPE)
        printf(" Broken pipe (POSIX). \r\n");
    else if (signo == MANPROCSIG_ALRM)
        printf(" Alarm clock (POSIX). \r\n");
    else if (signo == MANPROCSIG_TERM)
        printf(" Termination (ANSI). \r\n");
    else if (signo == MANPROCSIG_STKFLT)
        printf(" Stack fault. \r\n");
    else if (signo == MANPROCSIG_CLD)
        printf(" Same as SIGCHLD (System V). \r\n");
    else if (signo == MANPROCSIG_CHLD)
        printf(" Child status has changed (POSIX). \r\n");
    else if (signo == MANPROCSIG_CONT)
        printf(" Continue (POSIX). \r\n");
    else if (signo == MANPROCSIG_STOP)
        printf(" Stop, unblockable (POSIX). \r\n");
    else if (signo == MANPROCSIG_TSTP)
        printf(" Keyboard stop (POSIX). \r\n");
    else if (signo == MANPROCSIG_TTIN)
        printf(" Background read from tty (POSIX). \r\n");
    else if (signo == MANPROCSIG_TTOU)
        printf(" Background write to tty (POSIX). \r\n");
    else if (signo == MANPROCSIG_URG)
        printf(" Urgent condition on socket (4.2 BSD). \r\n");
    else if (signo == MANPROCSIG_XCPU)
        printf(" CPU limit exceeded (4.2 BSD). \r\n");
    else if (signo == MANPROCSIG_XFSZ)
        printf(" File size limit exceeded (4.2 BSD). \r\n");
    else if (signo == MANPROCSIG_VTALRM)
        printf(" Virtual alarm clock (4.2 BSD). \r\n");
    else if (signo == MANPROCSIG_PROF)
        printf(" Profiling alarm clock (4.2 BSD). \r\n");
    else if (signo == MANPROCSIG_WINCH)
        printf(" Window size change (4.3 BSD, Sun). \r\n");
    else if (signo == MANPROCSIG_POLL)
        printf(" Pollable event occurred (System V). \r\n");
    else if (signo == MANPROCSIG_IO)
        printf(" I/O now possible (4.2 BSD). \r\n");
    else if (signo == MANPROCSIG_PWR)
        printf(" Power failure restart (System V). \r\n");
    else if (signo == MANPROCSIG_SYS)
        printf(" Bad system call. \r\n");
    else if (signo == MANPROCSIG_UNUSED)
        printf(" Unknow erroe. \r\n");
    Exception_frame *p = Exception_stack;
    Exception_stack = Exception_stack->prev;
    longjmp(p->env, signo);
    // exit(0);
    //exit process
}