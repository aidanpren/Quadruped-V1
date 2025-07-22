#include "leg.h"
#include <Arduino.h>

Leg::Leg(int hipPin, int shoulderPin, int kneePin)
{
    _hipPin = hipPin;
    _shoulderPin = shoulderPin;
    _kneePin = kneePin;
}
void Leg::printPins()
{
    Serial.print("Hip Pin: ");
    Serial.println(_hipPin);
    Serial.print("Shoulder Pin: ");
    Serial.println(_shoulderPin);
    Serial.print("Knee Pin: ");
    Serial.println(_kneePin);
}