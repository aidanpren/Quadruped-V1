#include "leg.h"
#include "IKController.h"
#include "gait_controller.h"
#include <Arduino.h>

Leg frontLeft(40.6, 140, 140, 1, 2, 3);
Leg frontRight(40.6, 140, 140, 4, 5, 6);
Leg backLeft(40.6, 140, 140, 7, 8, 9);
Leg backRight(40.6, 140, 140, 10, 11, 12);

GaitController gaitController;
// Replace the following line with the correct constructor arguments for IKController.
// For example, if IKController requires three float parameters:
IKController ikController(40.6, 140, 140);

Leg legControllers[4] = {frontLeft, frontRight, backLeft, backRight};

void setup()
{
    Serial.begin(9600);
    delay(1000);

    frontLeft.moveTo(0, 40.6, -280.0);
}

void loop()
{
    gaitController.update();

    for (int i = 0; i < 4; i++)
    {
        Vec3 pos = gaitController.getFootTarget(i);
        JointAngles angles = ikController.calculateIK(pos.x, pos.y, pos.z);
        legControllers[i].moveTo(angles.j1, angles.j2, angles.j3);
        if (i == 2) // Example for debugging only the third leg
        {
            Serial.print("Leg ");
            Serial.print(i);
            Serial.print(" target position: x=");
            Serial.print(pos.x);
            Serial.print(", y=");
            Serial.print(pos.y);
            Serial.print(", z=");
            Serial.println(pos.z);
        }
    };

    delay(100); // Adjust delay as needed for smoother movement
}
