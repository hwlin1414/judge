#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <jail.h>
#include <sys/param.h>
#include <sys/jail.h>
#include <sys/types.h>
#include <sys/uio.h>

int main(int argc, char **argv){
    struct jail j = {JAIL_API_VERSION, "/usr/jails/judge", "judge", "judge", 0, 0, NULL, NULL};
    pid_t pid;
    int jid;

    while(1){
        pid = fork();
        if(pid == 0){
            jail(&j);
            system("ls /root/");
            while(1) sleep(1);
            exit(0);
        }
        sleep(1);
        system("jls");
        kill(pid, SIGKILL);
        sleep(1);
    }
    return 0;
}
