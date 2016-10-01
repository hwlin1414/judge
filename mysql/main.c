#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main(void){
    MYSQL mysql, *sock;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int i;
    
    mysql_init(&mysql);
    sock = mysql_real_connect(&mysql, "localhost", "coding", "passwd", "coding", 0, NULL, 0);
    if(sock == NULL){
        fprintf(stderr, "error: %s", mysql_error(&mysql));
        perror("");
        exit(1);
    }

    if(mysql_query(sock, "SHOW TABLES;")){
        fprintf(stderr,"Query failed (%s)\n",mysql_error(sock));
        exit(1);
    }

    res = mysql_store_result(sock);
    if(res == NULL){
        fprintf(stderr,"Couldn't get result from %s\n", mysql_error(sock));
        exit(1);
    }
    while((row = mysql_fetch_row(res)) != NULL){
        for(i = 0; i < (int)mysql_num_fields(res); i++){
            if(i != 0) printf("\t|");
            printf("%s", (((row[i]==NULL)&&(!strlen(row[i]))) ? "NULL" : row[i]));
        }
        printf("\n");
    } 
    
    mysql_free_result(res);
    mysql_close(sock);

    return 0;
}
