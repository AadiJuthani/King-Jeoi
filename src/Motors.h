#pragma once
#include <Arduino.h>

class Motors {
public:
    void setup();

    void forward(int speed);
    void back(int speed);
    void rotateRight(int speed);
    void rotateLeft(int speed);
    void turnRight(int speed);
    void turnLeft(int speed);
    void stop();
};