#include "leg.h"
#include <Arduino.h>

Leg frontLeft(1,2,3);
Leg frontRight(4,5,6);
Leg backLeft(7,8,9);
Leg backRight(10,11,12);

void setup() {
    Serial.begin(9600);
    delay(1000);

    Serial.println("Pin setup complete. Printing leg pins:");
    delay(1000);
    frontLeft.printPins();
    delay(500);
    frontRight.printPins();
    delay(500);
    backLeft.printPins();
    delay(500);
    backRight.printPins();
    
}

void loop() {

}