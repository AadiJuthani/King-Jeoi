#pragma once
#include "Motors.h"
#include "LineSensors.h"

class States {
public:
    void fight(Motors &motors, LineSensors &line);
    void defaultState(Motors &motors, LineSensors &line, int LSideRead, int RSideRead, int LFrontRead, int RFrontRead, int LLine, int RLine);
    void start(Motors &motors, LineSensors &line);
    void blindSearch(Motors &motors, LineSensors &line);

    bool matchStarted = false;

    enum HexState {
        HEX_FORWARD,
        HEX_TURN
    };

    HexState hexState = HEX_FORWARD;

    unsigned long hexTimer = 0;

    void hexagonSearch(Motors &motors, LineSensors &line);
    void rampForward(Motors &motors, double targetSpeed);
};