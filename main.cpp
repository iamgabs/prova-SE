/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
using namespace std::chrono;

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

InterruptIn button(BUTTON1);
DigitalOut led(LED1);

typedef struct jogador {
    AnalogIn y;
    int score;
} jogador_t;

void imprimirTabuleiro() {

}

int main(){
    jogador_t jogador1 = {PA_4, 0};
    jogador_t jogador2 = {PA_1, 0};

    while (true) {
        imprimirTabuleiro();
        ThisThread::sleep_for(BLINKING_RATE);                      
    }
}
