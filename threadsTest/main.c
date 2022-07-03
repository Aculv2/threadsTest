#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>

sem_t sem1,sem2,sem_start;

void *bh1750(void *arg){
    while(1) {
        sem_wait(&sem_start);
        //lux = measureLuminosity();
        printf("bh1750 Lux\n");
        sem_post(&sem1);
    }
};

void *bmp280(void *arg){
    while(1) {
        sem_wait(&sem1);
        //hPa = measurepressure();
        printf("Bar\n");
        sem_post(&sem2);
    }
};

void *max7219(void *arg){
    while(1) {
        sem_wait(&sem2);
        printf("Output\n");
        //LEDoutput();
        //LEDoutput();
        Sleep(5000);
        sem_post(&sem_start);
    }
};



int main(int argc, char* argv[]) {

    int *lux;       //return value bh1750
    double *hPa;    //return value bmp280

    sem_init(&sem1, 0, 0);   //erster parameter address der semaphore, zweiter 0 wenn ohne prozess gearbeitet wird
    sem_init(&sem2, 0, 0);
    sem_init(&sem_start, 0, 1);

    pthread_t t1, t2, t3;
    if (pthread_create(&t1, NULL, &bh1750, &lux) != 0) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &bmp280, &hPa) != 0) {
        return 1;
    }
    if (pthread_create(&t3, NULL, &max7219, NULL) != 0) {
        return 1;
    }
    //printf("bmp280\n");
    //printf("bh1750\n");

    /*
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    sem_destroy(&sem_start);
    */
    return 0;
}
