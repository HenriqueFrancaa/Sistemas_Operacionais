#include <stdio.h>
#include <pthread.h>


void *thread_de1a100(){
    for(int i = 1; i <= 100; i++){
        printf("Valor: %d\n", i);
    }
}

void *thread_de101a200(){
    for(int i = 101; i <= 200; i++){
        printf("Valor: %d\n", i);
    }
}

int main(){
    pthread_t t1, t2;

    puts("fim do main\n");
    pthread_create(&t1,NULL,thread_de1a100,NULL);
    pthread_join(t1,NULL);

    pthread_create(&t2,NULL,thread_de101a200,NULL);
    pthread_join(t2,NULL);

    pthread_exit(0);
    return 0;
}