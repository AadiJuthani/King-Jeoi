#include <Arduino.h>
#include <Servo.h>

#include "Pins.h"
#include "Motors.h"
#include "LineSensors.h"
#include "States.h"

Motors motors;
LineSensors line;
States states;

Servo myServo;

enum RunMode {
    fightMode,
    startMode,
    stopMode,
    blindMode
};

void setup() {

    Serial.begin(9600);

    motors.setup();
    line.setup();

    pinMode(StartMod, INPUT);
    pinMode(DIP1, INPUT);
    pinMode(DIP2, INPUT);

    myServo.attach(SERVO_PIN);
    myServo.write(10);

    while(!digitalRead(StartMod)){}
    delay(5000);
}

void loop() {

    myServo.write(80);

    RunMode mode;

    if(analogRead(DIP1) > 500 && analogRead(DIP2) > 500)
        mode = fightMode;

    else if(analogRead(DIP1) < 500 && analogRead(DIP2) < 500)
        mode = startMode;

    else if(analogRead(DIP1) < 500 && analogRead(DIP2) > 500)
        mode = blindMode;

    else
        mode = stopMode;

    switch(mode) {

        case fightMode:
            states.fight(motors,line);
            break;

        case startMode:
            states.start(motors,line);
            break;

        case blindMode:
            states.blindSearch(motors,line);
            break;

        case stopMode:
            motors.stop();
            break;
    }
}