#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <time.h>

typedef pthread_mutex_t mutex_t;
typedef pthread_t thread;

mutex_t mutex;
//int rua[5] = {32,32,32,32,32};

/*
*/
void *rua_horizontal(){
    pthread_mutex_lock(&mutex);
    int j = 0, i = 1;
    srand(time(NULL));
    int t = rand() % 10 + 1;
    while(j < t*5+1){
        int rua[5] = {32, 32, 32, 32, 32};

        rua[i % 5] = 67;
        i = i + 1;
        printf("\n\n");
        printf("               rua 1\n");
        printf("             +      +\n");
        printf("             |      |\n");
        printf("             +------+\n");
        printf("             |  C   |\n");
        printf("      +--+---+\033[31m------\033[39m+---+--+\n");
        printf("rua 4 %c  | %c\033[32m |\033[39m  %c   | %c | %c  rua 2\n", rua[0],rua[1],rua[2],rua[3],rua[4]);
        printf("      +--+---+------+---+--+\n");
        printf("             |      |\n");
        printf("             +------+\n");
        printf("             |      |\n");
        printf("             +      +\n");
        printf("               rua 3\n\n\n");
        usleep(199000);
        system("clear");
        j++;
    }
    pthread_mutex_unlock(&mutex);
}

void *rua_vertical(){
    pthread_mutex_lock(&mutex);
    int j = 0, i = 1;
    srand(time(NULL));
    int t = rand() % 10 + 1;
    while(j < t*5+1){
        int rua[5] = {32, 32, 32, 32, 32};
        rua[i % 5] = 67;
        i = i + 1;

        printf("\n\n");
        printf("               rua 1\n");
        printf("             +      +\n");
        printf("             |  %c   |\n", rua[0]);
        printf("             +------+\n");
        printf("             |  %c   |\n", rua[1]);
        printf("      +--+---+\033[32m------\033[39m+---+--+\n");
        printf("rua 4    | C \033[31m|\033[39m  %c   |   |    rua 2\n", rua[2]);
        printf("      +--+---+------+---+--+\n");
        printf("             |  %c   |\n", rua[3]);
        printf("             +------+\n");
        printf("             |  %c   |\n", rua[4]);
        printf("             +      +\n");
        printf("               rua 3\n\n\n");
        usleep(199000);
        system("clear");
        j++;
    }
    pthread_mutex_unlock(&mutex);
}

int main(){

    thread t1,t2;

    pthread_mutex_init(&mutex,NULL); 
    while(1){
        srand(time(NULL));
        int r = rand() % 2;
        system("clear");
        if(r){
            pthread_create(&t1,NULL,rua_horizontal,NULL);
            pthread_create(&t2,NULL,rua_vertical,NULL);
        }
        else{
            pthread_create(&t2,NULL,rua_vertical,NULL);
            pthread_create(&t1,NULL,rua_horizontal,NULL);
        }
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}