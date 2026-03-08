#include <Arduino.h>

#include "Pins.h"
#include "Motors.h"
#include "LineSensors.h"
#include "States.h"

// Hardware objects
Motors motors;
LineSensors line;
States states;

// Robot modes
enum RunMode {
    fightMode,
    startMode,
    stopMode,
    blindMode
};

void setup() {

    Serial.begin(9600);

    // Initialize hardware
    motors.setup();
    line.setup();

    pinMode(StartMod, INPUT);
    pinMode(DIP1, INPUT);
    pinMode(DIP2, INPUT);

    // Wait for competition start signal
    while(!digitalRead(StartMod)) {}

    // Competition delay
    delay(5000);
}

void loop() {

    RunMode mode;

    // Determine mode using DIP switches
    if(analogRead(DIP1) > 500 && analogRead(DIP2) > 500)
        mode = fightMode;

    else if(analogRead(DIP1) < 500 && analogRead(DIP2) < 500)
        mode = startMode;

    else if(analogRead(DIP1) < 500 && analogRead(DIP2) > 500)
        mode = blindMode;

    else
        mode = stopMode;

    // Execute behavior
    switch(mode) {

        case fightMode:
            states.fight(motors, line);
            break;

        case startMode:
            states.start(motors, line);
            break;

        case blindMode:
            states.blindSearch(motors, line);
            break;

        case stopMode:
            motors.stop();
            break;
    }
}