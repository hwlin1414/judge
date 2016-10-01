#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(void){
    int i;
    printf("hello world\n");
    for(i = 0; i < 3; i++){
        sleep(1);
    }
    unlink("123.out");
    return 0;
}
