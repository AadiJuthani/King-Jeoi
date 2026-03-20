#include "LineSensors.h"
#include "Pins.h"

void LineSensors::setup() {
    pinMode(LINE_LEFT, INPUT);
    pinMode(LINE_RIGHT, INPUT);

    pinMode(LSensor, INPUT);
    pinMode(RSensor, INPUT);
    pinMode(Lside, INPUT);
    pinMode(Rside, INPUT);

    pinMode(LED_PIN, OUTPUT);
}

bool LineSensors::leftLine() {
    return analogRead(LINE_RIGHT) < 100;
}

bool LineSensors::rightLine() {
    return analogRead(LINE_LEFT) < 100;
}

void LineSensors::lineRight(Motors &motors) {
    motors.back(140);
    delay(100);
    motors.rotateLeft(240);
    delay(50);
    motors.stop();
    // motors.back(140);
    // delay(180);
    // motors.rotateLeft(130);
    // delay(100);
    // motors.stop();
}

void LineSensors::lineLeft(Motors &motors) {
    motors.back(140);
    delay(100);
    motors.rotateRight(240);
    delay(50);
    motors.stop();
    // motors.back(140);
    // delay(180);
    // motors.rotateLeft(120);
    // delay(100);
    // motors.stop();
}