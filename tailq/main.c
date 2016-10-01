#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

TAILQ_HEAD(tailhead, entry) ;
struct entry {
    int num;
    int padding;
    TAILQ_ENTRY(entry) entries;     /* Tail queue. */
};

int main(void){
    char buf[BUFSIZ];
    struct entry *n1, *n2, *n3, *n4, *np;
    struct tailhead head;
    
    TAILQ_INIT(&head);
    n1 = malloc(sizeof(struct entry));
    n1->num = 10;
    TAILQ_INSERT_HEAD(&head, n1, entries);

    n2 = malloc(sizeof(struct entry));
    n2->num = 20;
    TAILQ_INSERT_TAIL(&head, n2, entries);

    n3 = malloc(sizeof(struct entry));
    n3->num = 30;
    TAILQ_INSERT_TAIL(&head, n3, entries);

    n4 = malloc(sizeof(struct entry));
    n4->num = 40;
    TAILQ_INSERT_TAIL(&head, n4, entries);

    np = TAILQ_FIRST(&head);
    while(fgets(buf, BUFSIZ, stdin) != NULL){
        if(strcmp(buf, "\n") == 0){
            if(TAILQ_NEXT(np, entries) != NULL)
                np = TAILQ_NEXT(np, entries);
        }else{
            if(TAILQ_PREV(np, tailhead, entries) != NULL)
                np = TAILQ_PREV(np, tailhead, entries);
        }
        printf("%d\n", np->num);
    }
    return 0;
}
