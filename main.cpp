/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <string>
#include <iostream>
#include <time.h>
#include <cstdio>

#include <cstdint>
#include "string.h"
#include "stdio.h"
using namespace std;
using namespace chrono;

#define __use_no_semihosting

// Blinking rate in milliseconds
//#define BLINKING_RATE 500ms
#define BLINKING_RATE 1000ms

using namespace std;

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

typedef struct jogador {
    AnalogIn y;
    DigitalIn sw;
    int score;
} jogador_t;

jogador_t jogador1 = {PA_4, PF_1, 0};
jogador_t jogador2 = {PA_1, PB_0, 0};

enum eDirection {
    STOP = 0,
    LEFT = 1,
    UPLEFT = 2,
    DOWNLEFT = 3,
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6
};


void setTextColor(const char* color) {
    // função para mudar a cor do texto de acordo com o valor
    cout << color;
}

void setBackgroundColor(const char* color) {
    // função para mudar a cor do fundo com o valor
    cout << color;
}


struct Ball_t {
    int x, y, originalX, originalY;
    eDirection direction;

    Ball_t() {
        x = y = originalX = originalY = 0;
        direction = STOP;
    }

    Ball_t(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }

    void reset() {
        x = originalX;
        y = originalY;
        direction = STOP;
    }

    void changeDirection(eDirection d) {
        direction = d;
    }

    void randomDirection() {
        direction = static_cast<eDirection>(rand() % 6 + 1);
    }

    void move() {
        switch (direction) {
            case STOP:
                break;
            case LEFT:
                x--;
                break;
            case UPLEFT:
                x--;
                y--;
                break;
            case RIGHT:
                x++;
                break;
            case DOWNLEFT:
                x--;
                y++;
                break;
            case UPRIGHT:
                x++;
                y--;
                break;
            case DOWNRIGHT:
                x++;
                y++;
                break;
            default:
                break;
        }
    }
};

struct PlayersBar_t {
    int x, y, originalX, originalY;

    PlayersBar_t() {
        x = y = originalX = originalY = 0;
    }

    PlayersBar_t(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }

    void reset() {
        x = originalX;
        y = originalY;
    }

    void moveUp() { y--; }
    void moveDown() { y++; }
};

struct Management_t {
    int width, height;
    int score1, score2;
    Ball_t ball;
    PlayersBar_t player1;
    PlayersBar_t player2;

    Management_t(int w, int h) {
        srand(time(NULL));
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = Ball_t(w / 2, h / 2);
        player1 = PlayersBar_t(1, h / 2 - 3);
        player2 = PlayersBar_t(w - 2, h / 2 - 3);
    }

    void scoreUp(PlayersBar_t &player) {
        if (&player == &player1) {
            score1++;
        } else {
            score2++;
        }
        ball.reset();
        player1.reset();
        player2.reset();
    }

    		
    void drawBoard() {
        cout << "\033[2J\033[H";
        cout << "\033[H";

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int ballx = ball.x;
                int bally = ball.y;
                int player1x = player1.x;
                int player2x = player2.x;

                int player1y = player1.y;
                int player2y = player2.y;

                if (j == 0 || j == width - 2) {
                    setBackgroundColor(BG_AZUL);
                    setTextColor(TXT_AZUL);
                    cout << " "; 
                } else if (ballx == j && bally == i) {
                    setBackgroundColor(BG_AZUL);
                    setTextColor(TXT_BRANCO);
                    cout << "O"; // Imprimir a bola
                } else if ((player1x + 1 == j || player1x + 2 == j) && i >= player1y && i < player1y + 4) {
                    setBackgroundColor(BG_AZUL);
                    setTextColor(TXT_BRANCO);
                    cout << "\xDB"; // Imprimir o jogador 1
                } else if ((player2x - 1 == j || player2x - 2 == j) && i >= player2y && i < player2y + 4) {
                    setBackgroundColor(BG_AZUL);
                    setTextColor(TXT_BRANCO);
                    cout << "\xDB"; // Imprimir o jogador 2
                } else {
                    setBackgroundColor(BG_AZUL);
                    setTextColor(TXT_AZUL);
                    cout << " ";
                }
            }
            cout << RESET << endl;
        }

    }

    void movePlayers() {
        ball.move();

        int ballx = ball.x;
        int bally = ball.y;
        int player1x = player1.x;
        int player2x = player2.x;

        int player1y = player1.y;
        int player2y = player2.y;

        //if(jogador1.y.read_u16() > 34000) {
        if(jogador1.y.read() > 0.7) {
            player1.moveUp();
        } else if (jogador1.y.read() < 0.3) {
            player1.moveDown();
        } 

        if(jogador2.y.read() > 0.7) {
            player2.moveUp();
        } else if (jogador2.y.read() < 0.3) {
            player2.moveDown();
        }         

        if(ball.direction == STOP) {
            ball.randomDirection();
        }
    }

    void check() {
        // fazer as colisões
        int ballx = ball.x;
        int bally = ball.y;
        int player1x = player1.x;
        int player2x = player2.x;

        int player1y = player1.y;
        int player2y = player2.y;

        // jogador 1
        for(int i = 0; i < 4 ; i++) {
            if(ballx == player1x + 1) {
                if (bally == player1y + 1) {
                    ball.changeDirection((eDirection)((rand() % 3) + 4));
                }
            }
        }

        // jogador 2
        for(int i = 0; i < 4 ; i++) {
            if(ballx == player2x - 1) {
                if (bally == player2y + 1) {
                    ball.changeDirection((eDirection)((rand() % 3) + 1));
                }
            }
        }

        // parte de cima
        if(bally == 0) {
            ball.changeDirection((eDirection) ball.direction == UPRIGHT ? DOWNRIGHT : DOWNLEFT );
        }

        // parte de baixo
        if(bally == height - 1) {
            ball.changeDirection((eDirection) ball.direction == DOWNRIGHT ? UPRIGHT : UPLEFT );
        }

        // colisões laterais (incrementar score dos players)
        // parede direita
        if(ballx == width - 1) {
            scoreUp(player1);
        }

        // parade esquerta
        if(ballx == 0) {
            scoreUp(player2);
        }
    }

    void start() {
        drawBoard();
        movePlayers();
        check();
    }
};

int main(){

    Timer t;
    t.start();

    //BufferedSerial pc(USBTX, USBRX, 330400);
    BufferedSerial pc(USBTX, USBRX, 144000);
    // usbtx = pb_3
    // usbrx = pa_10
    // TODO implementar limete dos players para não sair do tabuleiro, ajustar colisão
    Management_t c(125, 25);
    int h = 0, v = 0;

    char resultado[20];

    Ticker ticker;

    while (true) {

        //c.start();

        //ticker.attach(c.start, 0.2);

        memset(resultado, 0, sizeof(resultado)/sizeof(resultado[0]));
        sprintf(resultado, "\033[%d;%dH", h++, v++);

        if(h > 40){
            h = 2;
            v = 5;
        }
        
        cout << resultado;
        cout << "A";

        ThisThread::sleep_for(BLINKING_RATE);
    }
}

