#include "leg.h"
#include "IKController.h"
#include <Arduino.h>

Leg frontLeft(40.6, 140, 140, 1, 2, 3);
Leg frontRight(40.6, 140, 140, 4, 5, 6);
Leg backLeft(40.6, 140, 140, 7, 8, 9);
Leg backRight(40.6, 140, 140, 10, 11, 12);

void setup()
{
    Serial.begin(9600);
    delay(1000);

    frontLeft.moveTo(0, 40.6, -280.0);
}

void loop()
{
}