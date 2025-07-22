#ifndef LEG_H
#define LEG_H

class Leg {
public:
    Leg(int hipPin, int shoulderPin, int kneePin);
    void printPins();

private:
    int _hipPin;
    int _shoulderPin;
    int _kneePin;
};

#endif