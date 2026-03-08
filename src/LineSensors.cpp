#include "LineSensors.h"
#include "Pins.h"

void LineSensors::setup() {
    pinMode(A0_LEFT, INPUT);
    pinMode(A1_RIGHT, INPUT);

    pinMode(LSensor, INPUT);
    pinMode(RSensor, INPUT);
    pinMode(Lside, INPUT);
    pinMode(Rside, INPUT);

    pinMode(LED_PIN, OUTPUT);
}

bool LineSensors::leftLine() {
    return analogRead(A1_RIGHT) < 100;
}

bool LineSensors::rightLine() {
    return analogRead(A0_LEFT) < 100;
}

void LineSensors::lineRight(Motors &motors) {
    motors.back(140);
    delay(180);
    motors.rotateRight(130);
    delay(100);
    motors.stop();
}

void LineSensors::lineLeft(Motors &motors) {
    motors.back(140);
    delay(180);
    motors.rotateLeft(120);
    delay(100);
    motors.stop();
}