#include "mbed.h"
#include "Management.h"

// Blinking rate in milliseconds
#define BLINKING_RATE 1000ms

int main()
{
    BufferedSerial pc(USBTX, USBRX, 460800);
    Management c(125, 25);

    while (true) {
        c.start();
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
