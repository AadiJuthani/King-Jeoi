#include "States.h"
#include "Pins.h"
#include <Arduino.h>

#define HEX_EDGE_TIME  350
#define HEX_TURN_TIME  200
#define RAMP_STEPS     3
#define RAMP_DELAY_MS  4

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

    if(hexState == HEX_FORWARD) {

        motors.forward(60);

        if(analogRead(LINE_LEFT) < 100 || analogRead(LINE_RIGHT) < 100) {
            motors.stop();
            hexState = HEX_TURN;
        }

    } else {

        motors.rotateRight(200);

        if(analogRead(LINE_LEFT) > 100 && analogRead(LINE_RIGHT) > 100) {
            motors.stop();
            hexState = HEX_FORWARD;
        }
    }
}

void States::rampForward(Motors &motors, double targetSpeed) {

    double step = targetSpeed / RAMP_STEPS;

    for(int i = 1; i <= RAMP_STEPS; i++) {

        motors.forward(step * i);

        delay(RAMP_DELAY_MS);
    }
}