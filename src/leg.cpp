#include "leg.h"
#include <Arduino.h>

Leg::Leg(float l1, float l2, float l3, int hipPin, int shoulderPin, int kneePin)
    : ik(l1, l2, l3), hipPin(hipPin), shoulderPin(shoulderPin), kneePin(kneePin) {
          // hipServo.attach(hipPin);
          // shoulderServo.attach(shoulderPin);
          // kneeServo.attach(kneePin);
      };

void Leg::moveTo(float x, float y, float z)
{
    JointAngles angles = ik.calculateIK(x, y, z);
}