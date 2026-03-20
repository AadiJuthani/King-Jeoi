#include "States.h"
#include "Pins.h"
#include <Arduino.h>

void States::defaultState(Motors &motors, LineSensors &line,
                          int LSideRead, int RSideRead,
                          int LFrontRead, int RFrontRead,
                          int LLine, int RLine) {

    // ===== ATTACK FRONT =====
    if(LFrontRead && RFrontRead) {
        rampForward(motors,255);
        return;
    }


    // ===== FRONT ANGLE CORRECTION =====
    if(RFrontRead) {
        motors.turnRight(240);
        return;
    }

    if(LFrontRead) {
        motors.turnLeft(240);
        return;
    }

    if(RSideRead) {
        //Implement juke then attack algorithm (tiki-tak)
        motors.rotateRight(240);
        return;
    }

    if(LSideRead) {
        //Implement juke then attack algorithm (tiki-tak)
        motors.rotateLeft(240);
        return;
    }

        // ===== LINE SAFETY =====
    if (RLine && LLine) {
        line.lineRight(motors);
        delay(250);
        return;
    }
    if(RLine) {
        line.lineRight(motors);
        delay(250);
        return;
    }

    if(LLine) {
        line.lineLeft(motors);
        delay(150);
        return;
    }

    hexagonSearch(motors, line);
}

void States::hexagonSearch(Motors &motors, LineSensors &line) {
    if(line.leftLine() || line.rightLine()) {
        motors.rotateRight(200);
        delay(300); // tuned to ~120°
        return;
    }
    motors.forward(60);
}

void States::rampForward(Motors &motors, double targetSpeed) {
    motors.forward(targetSpeed);
}