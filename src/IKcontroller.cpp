#include "IKcontroller.h"
#include <Arduino.h>
#include <math.h>

IKController::IKController(float l1, float l2, float l3)
{
    this->l1 = l1; // Length of the first link
    this->l2 = l2; // Length of the second link
    this->l3 = l3; // Length of the third link
}

JointAngles IKController::calculateIK(float x, float y, float z)
{
    JointAngles angles;

    float B = sqrt(x * x + y * y + z * z);
    float t1 = asin((sin(DEG_TO_RAD * 90) * l1) / B);
    float t2 = 90 - t1;
    float A = (sin(t2) * B) / sin(DEG_TO_RAD * 90);
    float j3 = acos(((A * A) - (l2 * l2) - (l3 * l3)) / -2 * l2 * l3);
    float j2 = asin((sin(j3) * l2) / A);
    float j1 = atan2(y, x);
    angles.j1 = RAD_TO_DEG * j1;
    angles.j2 = RAD_TO_DEG * j2;
    angles.j3 = RAD_TO_DEG * j3;

    // if (B> (sqrt(l1*l1 + (l2+l3)*(l2+l3)))) {
    //     angles.j1 = 90;
    //     angles.j2 = 90;
    //     angles.j3 = 90;
    //     Serial.println("Target is unreachable");
    // }

    return angles;
}

void IKController::moveTo(float x, float y, float z)
{
    JointAngles angles = calculateIK(x, y, z);

    // Here you would typically send the angles to the servos
    // For example:
    // servo1.write(angles.j1);
    // servo2.write(angles.j2);
    // servo3.write(angles.j3);

    Serial.print("Moving to: ");
    Serial.print("J1: ");
    Serial.print(angles.j1);
    Serial.print(", J2: ");
    Serial.print(angles.j2);
    Serial.print(", J3: ");
    Serial.println(angles.j3);
}