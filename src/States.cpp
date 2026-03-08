#include "States.h"
#include "Pins.h"
#include <Arduino.h>

#define HEX_EDGE_TIME  350
#define HEX_TURN_TIME  200
#define RAMP_STEPS     3
#define RAMP_DELAY_MS  4

void States::fight(Motors &motors, LineSensors &line) {

    if(line.rightLine()) { line.lineRight(motors); return; }
    if(line.leftLine())  { line.lineLeft(motors);  return; }

    if(digitalRead(LSensor) && digitalRead(RSensor)) {
        rampForward(motors,255);
        return;
    }

    if(digitalRead(Rside) && digitalRead(RSensor)) {
        motors.rotateRight(240);
        delay(90);
        return;
    }

    if(digitalRead(Lside) && digitalRead(LSensor)) {
        motors.rotateLeft(240);
        delay(90);
        return;
    }

    if(digitalRead(Rside)) {
        motors.rotateRight(240);
        delay(60);
        return;
    }

    if(digitalRead(Lside)) {
        motors.rotateLeft(240);
        delay(60);
        return;
    }

    if(digitalRead(RSensor)) {
        motors.turnRight(240);
        return;
    }

    if(digitalRead(LSensor)) {
        motors.turnLeft(240);
        return;
    }

    motors.forward(53);
}

void States::start(Motors &motors, LineSensors &line) {

    if(digitalRead(StartMod))
        matchStarted = true;

    if(!matchStarted) {
        motors.stop();
        return;
    }

    if(line.rightLine()) { line.lineRight(motors); return; }
    if(line.leftLine())  { line.lineLeft(motors);  return; }

    if(digitalRead(LSensor) && digitalRead(RSensor)) {
        rampForward(motors,255);
        return;
    }

    if(digitalRead(Rside) && digitalRead(RSensor)) {
        motors.rotateRight(240);
        delay(90);
        return;
    }

    if(digitalRead(Lside) && digitalRead(LSensor)) {
        motors.rotateLeft(240);
        delay(90);
        return;
    }

    if(digitalRead(Rside)) {
        motors.rotateRight(240);
        delay(60);
        return;
    }

    if(digitalRead(Lside)) {
        motors.rotateLeft(240);
        delay(60);
        return;
    }

    if(digitalRead(RSensor)) {
        motors.turnRight(240);
        return;
    }

    if(digitalRead(LSensor)) {
        motors.turnLeft(240);
        return;
    }

    motors.forward(63);
}

void States::blindSearch(Motors &motors, LineSensors &line) {

    if(!digitalRead(StartMod)) {
        motors.stop();
        return;
    }

    if(line.rightLine()) { line.lineRight(motors); return; }
    if(line.leftLine())  { line.lineLeft(motors);  return; }

    if(digitalRead(LSensor) && digitalRead(RSensor)) {
        rampForward(motors,255);
        return;
    }

    if(digitalRead(RSensor)) {
        motors.rotateRight(220);
        return;
    }

    if(digitalRead(LSensor)) {
        motors.rotateLeft(220);
        return;
    }

    if(digitalRead(Rside)) {
        motors.rotateRight(220);
        delay(250);
        return;
    }

    if(digitalRead(Lside)) {
        motors.rotateLeft(220);
        delay(250);
        return;
    }

    hexagonSearch(motors);
}

void States::hexagonSearch(Motors &motors) {

    if(hexState == HEX_FORWARD) {

        motors.forward(120);

        if(millis() - hexTimer > HEX_EDGE_TIME) {
            motors.stop();
            hexTimer = millis();
            hexState = HEX_TURN;
        }

    } else {

        motors.rotateRight(200);

        if(millis() - hexTimer > HEX_TURN_TIME) {
            motors.stop();
            hexTimer = millis();
            hexState = HEX_FORWARD;
        }
    }
}

void States::rampForward(Motors &motors, double targetSpeed) {

    double step = targetSpeed / RAMP_STEPS;

    for(int i=1;i<=RAMP_STEPS;i++) {

        motors.forward(step * i);

        delay(RAMP_DELAY_MS);
    }
}