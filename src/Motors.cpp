#include "Motors.h"
#include "Pins.h"

void Motors::setup() {
    pinMode(Rpos, OUTPUT);
    pinMode(Rneg, OUTPUT);
    pinMode(Lpos, OUTPUT);
    pinMode(Lneg, OUTPUT);
}

void Motors::forward(int speed) {
    analogWrite(Rpos, speed);
    analogWrite(Lpos, (speed+20>255) ? 255:speed+20);
    analogWrite(Rneg, 0);
    analogWrite(Lneg, 0);
}

void Motors::back(int speed) {
    analogWrite(Rpos, 0);
    analogWrite(Lpos, 0);
    analogWrite(Rneg, (speed+12+30>255) ? 255:speed+12+30);
    analogWrite(Lneg, (speed+30>255) ? 255:speed+30);
}

void Motors::rotateRight(int speed) {
    
    analogWrite(Rpos, 0);
    analogWrite(Rneg, (speed+20>255) ? 255:speed+20);
    analogWrite(Lpos, (speed+20+20>255) ? 255:speed+20+20);
    analogWrite(Lneg, 0);
}

void Motors::rotateLeft(int speed) {
    analogWrite(Rpos, speed);
    analogWrite(Rneg, 0);
    analogWrite(Lpos, 0);
    analogWrite(Lneg, (speed+20>255) ? 255:speed+20);
}

void Motors::turnRight(int speed) {
    analogWrite(Rpos, 0);
    analogWrite(Rneg, 0);
    int speed2 = (speed+20>255) ? 255:speed+20;
    analogWrite(Lpos, speed2);
    analogWrite(Lneg, 0);
}

void Motors::turnLeft(int speed) {
    analogWrite(Rpos, speed);
    analogWrite(Rneg, 0);
    analogWrite(Lpos, 0);
    analogWrite(Lneg, 0);
}

void Motors::stop() {
    analogWrite(Rpos, 0);
    analogWrite(Rneg, 0);
    analogWrite(Lpos, 0);
    analogWrite(Lneg, 0);
}

void Motors::forwardRamp(int targetSpeed, int rampStep, int rampDelay) {
    for(int s=0; s<=targetSpeed; s+=rampStep) {
        forward(s);
        delay(rampDelay);
    }
}