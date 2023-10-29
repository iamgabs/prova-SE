/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <string>

using namespace std;
using namespace chrono;

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

// definir cores
#define TXT_VERMELHO    "\033[31m" 
#define TXT_VERDE       "\033[31m"
#define TXT_AZUL        "\033[34m"
#define TXT_AMARELO     "\033[33m"
#define TXT_PRETO       "\033[30m"
#define TXT_BRANCO      "\033[97m"

// definir backgroud
#define BG_VERMELHO     "\033[41m"
#define BG_VERDE        "\033[42m"
#define BG_AZUL         "\033[44m"
#define BG_AMARELO      "\033[43m"
#define BG_PRETO        "\033[40m"
#define BG_BRANCO       "\033[107m"

// definir reset
#define RESET           "\033[0m"

// variáveis globais
Thread player1;
Thread player2;

typedef struct jogador {
    AnalogIn y;
    int score;
} jogador_t;


void setTextColor(char* color) {
    // função para mudar a cor do texto de acordo com o valor
    cout << color;
}

void setBackgroundColor(char* color) {
    // função para mudar a cor do fundo com o valor
    cout << color;
}

void imprimirTabuleiro() {
    // TODO
}

void func_thread_player1() {
    // TODO
    // função que será passada como callback para a thread "player1"
}

void func_thread_player2() {
    // TODO
    // função que será passada como callback para a thread "player2"
}

int main(){
    jogador_t jogador1 = {PA_4, 0};
    jogador_t jogador2 = {PA_1, 0};

    while (true) {
        imprimirTabuleiro();
        ThisThread::sleep_for(BLINKING_RATE);                      
    }
}
