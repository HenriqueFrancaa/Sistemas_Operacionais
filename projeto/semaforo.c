#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>

typedef pthread_mutex_t mutex;
typedef pthread_t thread;

#define VERMELHO    "\x1b[31m"
#define VERDE   "\x1b[32m"
#define RESET   "\x1b[0m"

typedef struct car{
    int id;
    int x;
    int y;
    int direction;   //1 -> vertical; 2 -> horizontal;
}car;

char* vertical;
char* horizontal;

int sinal;  // 1 -> aberto na vertical; 0 -> aberto na horizontal
int k1 = 0;
int k2 = 0;

struct car carros[2];
mutex Mutex;

int rua[5][5] = {
    {32,32,32,32,32},
    {32,32,32,32,32},
    {32,32,32,32,32},
    {32,32,32,32,32},
    {32,32,32,32,32}
};

void add(struct car carros[2]){
    for(int i = 0; i < 2; i++) {
        rua[carros[i].x][carros[i].y] = 'A' + i;
    }
}

struct car* mov(struct car* carro){
    rua[carro->x][carro->y] = 32;
    rua[carro->x][carro->y] = 32;
    rua[carro->x][carro->y] = 32;

    int direction = carro->direction;

    if(direction == 1){ 
        if(carro->x == 4){
            carro->x = 0;
        }
        else{
            carro->x = carro->x+1;
        }
    }
    else if(direction == 2) {
        if(carro->y == 4){
            carro->y = 0;
        }
        else{
            carro->y = carro->y+1;
        }
    }
    return carro;
}

void semaforo(int sinal){
    if(sinal == 1){
        vertical = VERMELHO;
        horizontal = VERDE;
    }
    else{
        vertical = VERDE;
        horizontal = VERMELHO;
    }
}

void *transito(){
    while(1){
        semaforo(sinal);
        printf("\n\n\n");
        printf("                 RUA 1               \n\n");
        printf("               |       |          \n");
        printf("               |   %c   |          \n", rua[0][2]);
        printf("               +-------+          \n");
        printf("               |       |          \n");
        printf("               |   %c   |          \n",rua[1][2]);
        printf("     ---+------+%s-------%s+------+---\n",horizontal,RESET);
        printf("RUA   %c |  %c   %s|%s   %c   |    %c | %c   RUA\n",rua[2][0], rua[2][1],vertical,RESET,rua[2][2],rua[2][3],rua[2][4]);
        printf(" 3      |      %s|%s       |      |      4\n",vertical,RESET);
        printf("     ---+------+-------+------+---\n");
        printf("               |   %c   |          \n",rua[3][2]);
        printf("               |       |          \n");
        printf("               +-------+          \n");
        printf("               |   %c   |          \n\n",rua[4][2]);
        printf("                 RUA 2                \n");
        printf("\n\n\n");
        sleep(1);
        system("clear");
    }
}

void criando_carros(){
    carros[0] = (struct car){1,0,2,1};
    carros[1] = (struct car){2,2,0,2};
}

void *func(void *arg){
    struct car *carro = (struct car *)arg;
    add(carros); 
    sleep(1);
    while(1){
        if((carro->x >= 0 && carro->x < 5) && (carro->y >= 0 && carro->y < 5)){
            if(carro->direction == 1){ 
                if(carro->x == 1 && carro->y == 2){ 
                    if(sinal == 1){ 
                        pthread_mutex_lock(&Mutex);
                        mov(carro);
                        add(carros);
                        sleep(1);
                        mov(carro);
                        add(carros);
                        sinal = 2;
                        sleep(1);
                        pthread_mutex_unlock(&Mutex);
                    }
                }else{ 
                    mov(carro);
                    add(carros);
                    sleep(1);
                }
            }
            if(carro->direction == 2){ 
                if((carro->x == 2 && carro->y == 1)){ 
                    if(sinal == 2 ){
                        pthread_mutex_lock(&Mutex);
                        mov(carro);
                        add(carros);
                        sleep(1);
                        mov(carro);
                        add(carros);
                        sinal = 1;
                        sleep(1);
                        pthread_mutex_unlock(&Mutex);
                    }
                }else{
                    mov(carro);
                    add(carros);
                    sleep(1);
                }
            }   
        }else{
            if(carro->x == 5){
                carro->x = 0;
                carro->y = 2;
            }
            else if(carro->y == 5){
                carro->y = 0;
                carro->x = 2;
            }
        }
        sleep(1);
    }
}

int main(void){
    criando_carros();
    srand(time(NULL));
    sinal = (rand() % 2) + 1;
    pthread_mutex_init(&Mutex,NULL);
    thread t1,t2,print;
    pthread_create(&print, NULL, transito, NULL);
    pthread_create(&t1,NULL,func,&carros[0]);
    pthread_create(&t2, NULL, func, &carros[1]);

    pthread_join(print, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&Mutex);

    return 0;
}