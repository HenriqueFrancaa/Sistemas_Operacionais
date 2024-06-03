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

int rua[5] = {32, 32, 32, 32, 32};

void *rua_horizontal(){
    pthread_mutex_lock(&mutex);
    int j = 0, i = 1;
    srand(time(NULL));
    int t = rand() % 10 + 1;
    while(j < t*5+1){
        rua[i % 5] = 65;
        printf("\n\n");
        printf("                     rua 1 \n");
        printf("                  +        +\n");
        printf("                  |        |\n");
        printf("                  |        |\n");
        printf("                  |--------|\n");
        printf("                  |        |\n");
        printf("                  |   B    |\n");
        printf("      +-----------+\033[31m--------\033[39m+-----------+\n");
        printf("            |     \033[32m|\033[39m        |     |          \n");
        printf("rua 4   %c   |  %c  \033[32m|\033[39m    %c   |  %c  |  %c    rua 2\n", rua[0], rua[1], rua[2], rua[3], rua[4]);
        printf("            |     \033[32m|\033[39m        |     |          \n");
        printf("      +-----------+--------+-----------+\n");
        printf("                  |        |\n");
        printf("                  |        |\n");
        printf("                  |--------|\n");
        printf("                  |        |\n");
        printf("                  |        |\n");
        printf("                  +        +\n");
        printf("                     rua 3 \n\n");
        usleep(199000);
        system("clear");
        j++;
        rua[i % 5] = 32;
        i = i + 1;
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void *rua_vertical(){
    pthread_mutex_lock(&mutex);
    int j = 0, i = 1;
    srand(time(NULL));
    int t = rand() % 10 + 1;
    while(j < t*5+1){
        rua[i % 5] = 66;
        printf("\n\n");
        printf("                     rua 1 \n");
        printf("                  +        +\n");
        printf("                  |        |\n");
        printf("                  |   %c    |\n", rua[0]);
        printf("                  |--------|\n");
        printf("                  |        |\n");
        printf("                  |   %c    |\n", rua[1]);
        printf("      +-----------+\033[32m--------\033[39m+-----------+\n");
        printf("            |     \033[31m|\033[39m        |     |          \n");
        printf("rua 4       |  A  \033[31m|\033[39m   %c    |     |       rua 2\n", rua[2]);
        printf("            |     \033[31m|\033[39m        |     |          \n");
        printf("      +-----------+--------+-----------+\n");
        printf("                  |   %c    |\n", rua[3]);
        printf("                  |        |\n");
        printf("                  |--------|\n");
        printf("                  |   %c    |\n", rua[4]);
        printf("                  |        |\n");
        printf("                  +        +\n");
        printf("                     rua 3 \n\n");
        usleep(199000);
        system("clear");
        j++;
        rua[i % 5] = 32;
        i = i + 1;
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

int main(){
    thread t1,t2;
    

    while(1){
        pthread_mutex_init(&mutex,NULL);
        system("clear");
        srand(time(NULL));
        int r = rand() % 2;
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
        pthread_mutex_destroy(&mutex);
    }

    return 0;
}