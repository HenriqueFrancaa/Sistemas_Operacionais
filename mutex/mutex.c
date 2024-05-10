#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int i;
typedef pthread_t thread;
typedef pthread_mutex_t mutex_t;

mutex_t mutex;

void *func(){
    pthread_mutex_lock(&mutex);
    for(int i = 0; i <= 5; i++){
        printf("%d\n", i);
        sleep(1);
    }
    pthread_mutex_unlock(&mutex);
}
/*
o mutex que foi criado vai servir como um tipo de acesso para a area restrita
para evitar a concorrencia, logo as threads nao vao conseguir fazer o processo
de forma paralela, um vai precisar esperar o outro terminar para ter o acesso permitido
*/

int main(){
    pthread_mutex_init(&mutex, NULL); //iniciando o mutex
    thread t1,t2;

    pthread_create(&t1,NULL,func,NULL);
    pthread_create(&t2,NULL,func,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}