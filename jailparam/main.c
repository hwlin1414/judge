#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/jail.h>
#include <jail.h>

int main(int argc, char **argv){
    struct jailparam jp;
    int jid;

    jid = jail_setv(JAIL_CREATE, "name", "judge", "host.hostname", "judge", "path", "/usr/jails/judge", "persist", "true", NULL);

    printf("%d\n", jid);
    if(jid == -1){
        perror("jail_setv:");
        fprintf(stderr, "%s\n", jail_errmsg);
    }
    sleep(1);
    jid = jail_setv(JAIL_UPDATE, "name", "judge", "nopersist", "true", NULL);
    printf("%d\n", jid);
    if(jid == -1){
        perror("jail_setv:");
        fprintf(stderr, "%s\n", jail_errmsg);
    }
    return 0;
}
