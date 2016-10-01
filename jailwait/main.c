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
    struct jail j = {JAIL_API_VERSION, "/usr/jails/base", "judge", "judge", 0, 0, NULL, NULL};
    pid_t pid;
    int jid;

    pid = fork();
    if(pid == 0){
        if(jail(&j) < 0) perror("jail");
        sleep(1);
        system("ls -al ~/");
        printf("child finished!\n");
        exit(0);
    }
    waitpid(pid, NULL, 0);
    printf("waited!\n");
    return 0;
}
