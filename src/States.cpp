#include "States.h"
#include "Pins.h"
#include <Arduino.h>

void States::defaultState(Motors &motors, LineSensors &line,
                          int LSideRead, int RSideRead,
                          int LFrontRead, int RFrontRead,
                          int LLine, int RLine) {

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


    // ===== SIDE DETECTION =====
    if(RSideRead && RFrontRead) {
        motors.rotateRight(240);
        delay(90);
        return;
    }

    if(LSideRead && LFrontRead) {
        motors.rotateLeft(240);
        delay(90);
        return;
    }

    if(RSideRead) {
        //Implement juke then attack algorithm (tiki-tak)
        motors.rotateRight(240);
        delay(60);
        return;
    }

    if(LSideRead) {
        //Implement juke then attack algorithm (tiki-tak)
        motors.rotateLeft(240);
        delay(60);
        return;
    }

    motors.forward(80);
    // ===== BLIND SEARCH =====
    //hexagonSearch(motors, line);
}

void States::hexagonSearch(Motors &motors, LineSensors &line) {

    if(true) { //The condition will be something

        motors.forward(60);

        if(analogRead(LINE_LEFT) < 100 || analogRead(LINE_RIGHT) < 100) {
            motors.stop();
        }

    } else {

        motors.rotateRight(200);

        if(analogRead(LINE_LEFT) > 100 && analogRead(LINE_RIGHT) > 100) {
            motors.stop();
        }
    }
}

void States::rampForward(Motors &motors, double targetSpeed) {
    motors.forward(targetSpeed);
}