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
    pinMode(LSensor, INPUT);
    pinMode(RSensor, INPUT);

    while(!digitalRead(StartMod)) {}

    // Competition delay
    delay(2000); //Make 5000
}

void loop() {

    //Reading Sensors
    int LSideRead = digitalRead(Lside);
    int RSideRead = digitalRead(Rside);
    int LFrontRead = digitalRead(LSensor);
    int RFrontRead = digitalRead(RSensor);
    int LLine = line.leftLine();
    int RLine = line.rightLine();

    if (digitalRead(StartMod)) {
        states.defaultState(motors, line, LSideRead, RSideRead, LFrontRead, RFrontRead, LLine, RLine);
    } else {
        motors.forward(0);
    }
}