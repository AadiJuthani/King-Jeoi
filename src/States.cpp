#include "States.h"
#include "Pins.h"
#include <Arduino.h>

// Time in ms for a full 360° rotation at speed 240 - tune this
#define FULL_ROTATION_MS 1000UL // UL = unsigned long, keep this in.
#define DEGREES_120_MS   (FULL_ROTATION_MS * 120UL / 360UL)
#define DEGREES_40_MS    (FULL_ROTATION_MS * 40UL / 360UL)

void States::defaultState(Motors &motors, LineSensors &line,
                          int LSideRead, int RSideRead,
                          int LFrontRead, int RFrontRead,
                          int LLine, int RLine) {

    // ===== ATTACK FRONT =====
    if(LFrontRead && RFrontRead) {
        rampForward(motors,255);
        return;
    }

    if(RFrontRead) {
        motors.turnRight(240);
        return;
    }

    if(LFrontRead) {
        motors.turnLeft(240);
        return;
    }


    // ===== FRONT ANGLE CORRECTION =====
    if(RSideRead) {
        // Break position: dart away, then hunt
        motors.rotateRight(240);
        delay(DEGREES_40_MS);
        
        motors.forward(255);
        unsigned long startTime = millis();
        while(millis() - startTime < 150) {
            if(line.leftLine() || line.rightLine()) break;
        }
        // Loop handles the rest - rotateRight continues until front IR fires
        return;
    }

    if(LSideRead) {
        motors.rotateLeft(240);
        delay(DEGREES_40_MS);
        
        motors.forward(255);
        unsigned long startTime = millis();
        while(millis() - startTime < 150) {
            if(line.leftLine() || line.rightLine()) break;
        }
        return;
    }
    
    // Back-up simple code
    // if(RSideRead) {
    //     //Implement juke then attack algorithm (tiki-tak)
    //     motors.rotateRight(240);
    //     return;
    // }

    // if(LSideRead) {
    //     //Implement juke then attack algorithm (tiki-tak)
    //     motors.rotateLeft(240);
    //     return;
    // }

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
        delay(DEGREES_120_MS);
        return;
    }
    motors.forward(60);
}

void States::rampForward(Motors &motors, double targetSpeed) {
    motors.forward(targetSpeed);
}