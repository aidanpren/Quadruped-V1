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

    // Hip angle (j1): rotate to face the foot position
    float j1 = atan2(y, x); // angle in radians
    angles.j1 = RAD_TO_DEG * j1;

    // Shoulder frame: project foot position into hip-facing plane
    float hipToFoot = sqrt(x * x + y * y);
    float shoulderX = hipToFoot - l1; // from shoulder joint to foot, in xz plane
    float shoulderZ = -z;             // if z is downward

    // Distance from shoulder to foot
    float dist = sqrt(shoulderX * shoulderX + shoulderZ * shoulderZ);

    // Clamp distance to avoid NaN in acos
    float maxReach = l2 + l3 - 0.001;
    if (dist > maxReach)
        dist = maxReach;

    // Law of cosines
    float angleKnee = acos((l2 * l2 + l3 * l3 - dist * dist) / (2 * l2 * l3));
    float angleShoulder = acos((l2 * l2 + dist * dist - l3 * l3) / (2 * l2 * dist));
    float angleOffset = atan2(shoulderZ, shoulderX);

    float j2 = angleOffset + angleShoulder;
    float j3 = angleKnee;
    Serial.println("j3: " + String(RAD_TO_DEG * j3));

    angles.j2 = RAD_TO_DEG * j2;
    angles.j3 = RAD_TO_DEG * angleKnee;

    // Debug
    Serial.println("---- IK Debug ----");
    Serial.print("Input (x,y,z): ");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.print(", ");
    Serial.println(z);
    Serial.print("j1: ");
    Serial.println(angles.j1);
    Serial.print("j2: ");
    Serial.println(angles.j2);
    Serial.print("j3: ");
    Serial.println(angles.j3);
    Serial.println("------------------");

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