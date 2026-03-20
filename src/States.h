#pragma once
#include "Motors.h"
#include "LineSensors.h"

class States {
public:
    void defaultState(Motors &motors, LineSensors &line, int LSideRead, int RSideRead, int LFrontRead, int RFrontRead, int LLine, int RLine);

    bool matchStarted = false;

    void hexagonSearch(Motors &motors, LineSensors &line);
    void rampForward(Motors &motors, double targetSpeed);
};