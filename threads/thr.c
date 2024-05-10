#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_t threads[100];

void *func(){
    for(int i = 0; i <= 5; i++){
        printf("%d\n", i);
        sleep(1);
    }
}

/*
*/

int main(){
    pthread_create(&threads[0],NULL,func,NULL);
    pthread_create(&threads[1],NULL,func,NULL);
    pthread_create(&threads[2],NULL,func,NULL);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    pthread_join(threads[2],NULL);

    system("pause");
    return 0;
}