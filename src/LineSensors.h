#pragma once
#include <Arduino.h>
#include "Motors.h"

class LineSensors {
public:
    void setup();

    bool leftLine();
    bool rightLine();

    void lineLeft(Motors &motors);
    void lineRight(Motors &motors);
};