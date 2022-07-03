#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>

void *bmp280(){
    while(1) {
        //measurepressure();
        printf("bmp280 Bar\n");
        Sleep(5000);
    }
};

void *bh1750(){
    while(1) {
        //measureLuminosity();
        printf("bh1750 Lux\n");
        Sleep(5000);
    }
};

void *max7219(){
    while(1) {
    LEDoutput();
    LEDoutput();
    }
};

sem_t s1;

int main(int argc, char* argv[]) {
    sem_init(&s1, 0, 1);   //erster parameter address der semaphore, zweiter 0 wenn ohne prozess gearbeitet wird
    pthread_t p1, p2, p3;
    if (pthread_create(&p1, NULL, &bmp280, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&p2, NULL, &bh1750, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&p3, NULL, &max7219, NULL) != 0) {
        return 1;
    }

    sem_destroy(&s1);
    return 0;
}
