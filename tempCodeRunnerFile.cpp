#include <stdio.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

int conta;

void countdown(int seconds){

    for(int i = seconds - 1; i >= 0; i--){

        this_thread::sleep_for(milliseconds(1000));
        printf("tempo rimanente : %d\n", i);
        conta = i;
    }

    printf("tempo scaduto\n");

}

int main(){

    int duration = 1;
    conta = duration;

    thread countdownThrd(countdown, duration);

    for(int i = 0; i < 20; i++){

        if(!conta) break;

        this_thread::sleep_for(milliseconds(500));
        printf("sto lavorando...\n");
    }

    countdownThrd.join();

    return 0;

}