#include "gait_controller.h"
#include "leg.h"
#include <Arduino.h>
#include <algorithm>

void GaitController::update() {
    unsigned long now = millis(); // Get current time in milliseconds
    float dt = (now - lastUpdate) / 1000.0f; // Convert milliseconds to seconds
    lastUpdate = now; // Update lastUpdate to current time

    float gaitFrequency = speed + 1.5f; // Adjust gait frequency based on speed
    for (int i=0; i<4; i++) {
        float offset = (i==1 || i == 2) ? 0.5f : 0.0f; // Offset for legs 1 and 2
        phase[i] += gaitFrequency * dt;
        phase[i] = fmod(phase[i], 1.0f); // Keep phase in [0, 1)
    }
}

Vec3 GaitController::getFootTarget(int legIndex) {
    float p = phase[legIndex];
    float strideLength = 60.0f;
    float liftHeight = 30.0f;

    float z = liftHeight * std::max(0.0f, static_cast<float>(sin(2 * PI * p))); // foot lifts only on swing

    // Construct Vec3 using correct initialization (update as per Vec3 definition)
    Vec3 target;
    target.x = strideLength * directionX;
    target.y = 0.0f;
    target.z = -150.0f + z;
    return target;
}