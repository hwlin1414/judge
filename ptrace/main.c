#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <machine/reg.h>
#include <signal.h>
#include "/usr/src/sys/kern/syscalls.c"

int getcall(int);
int getcall (int pid)
{
    int status;

    struct reg registers;
    status = ptrace(PT_GETREGS, pid, (caddr_t) & registers, 0);
    if (status != 0) {
        return -1;
    }
    return (int)registers.r_rax;
}

int main(void)
{
    int pid, count = 0, call;

    pid = fork ();
    if (pid == -1) {
        fprintf (stderr, "Fork failed: %s\n", strerror (errno));
        exit (EXIT_FAILURE);
    } else if (pid == 0) {
        ptrace(PT_TRACE_ME, 0, 0, 0);
        execlp ("./test", "./test", NULL);
    } else {
        if (wait (0) == -1) {
            fprintf (stderr, "Wait failed.\n");
            exit (EXIT_FAILURE);
        }
        while (ptrace (PT_TO_SCE, pid, (caddr_t) 1, 0) == 0) {
        //while (ptrace (PT_SYSCALL, pid, (caddr_t) 1, 0) == 0) {
            if (wait (0) == -1) break;
            call = getcall (pid);
            if (call == -1) break;

            count++;
            printf ("#%03d id: %04d name: %-16s, allow [y/n]? ", count, call, syscallnames[call]);
            switch(getchar()){
                case 'N': case 'n':
                    printf("terminated\n");
                    kill(pid, SIGKILL);
                    break;
                case '\n':
                    break;
                default:
                    getchar();
            }

            ptrace (PT_TO_SCX, pid, (caddr_t) 1, 0);
            //ptrace (PT_SYSCALL, pid, (caddr_t) 1, 0);
            if (wait (0) == -1) break;
            //retval = getcall (pid);
        }
        printf ("total: %d system calls.\n", count);
    }
    return 0;
}
