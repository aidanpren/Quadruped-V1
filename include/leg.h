#ifndef LEG_H
#define LEG_H

#include "IKController.h"

class Leg {
public:
    Leg(float l1, float l2, float l3, int hipPin, int shoulderPin, int kneePin);
    void moveTo(float x, float y, float z);

private:
    int _hipPin;
    int _shoulderPin;
    int _kneePin;

    IKController ik;
    int hipPin, shoulderPin, kneePin;
};

#endif