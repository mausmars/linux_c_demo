#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>

void procmsg(const char *format, ...);
void run_target(const char *programname);
void run_debugger(pid_t child_pid);

int main(int argc, char **argv) {
    pid_t child_pid;

    if (argc < 2) {
        fprintf(stderr, "Expected a program name as argument");
        return -1;
    }

    child_pid = fork();
    if (child_pid == 0)
        run_target(argv[1]);
    else if (child_pid > 0)
        run_debugger(child_pid);
    else {
        perror("fork");
        return -1;
    }
    return 0;
}

/* Print a message to stdout, prefixed by the process ID */
void procmsg(const char *format, ...) {
    va_list ap;
    fprintf(stdout, "[%d] ", getpid());
    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);
}

void run_target(const char *programname) {
    procmsg("target started. will run '%s'", programname);

    /* Allow tracing of this process */
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
        perror("ptrace");
        return;
    }
    /* Replace this process's image with the given program */
    execl(programname, programname, (char *) 0);
}

void run_debugger(pid_t child_pid) {
    int wait_status;
    unsigned icounter = 0;
    procmsg("debugger started");

    /* Wait for child to stop on its first instruction */
    wait(&wait_status);

    while (WIFSTOPPED(wait_status)) {
        icounter++;
        struct user_regs_struct regs;
        ptrace(PTRACE_GETREGS, child_pid, 0, &regs);
        unsigned instr = ptrace(PTRACE_PEEKTEXT, child_pid, regs.rip, 0);

        procmsg("icounter = %u.  IP = 0x%08x.  instr = 0x%08x",
                icounter, regs.rip, instr);

        /* Make the child execute another instruction */
        if (ptrace(PTRACE_SINGLESTEP, child_pid, 0, 0) < 0) {
            perror("ptrace");
            return;
        }
        /* Wait for child to stop on its next instruction */
        wait(&wait_status);
    }
    procmsg("the child executed %u instructions", icounter);
}