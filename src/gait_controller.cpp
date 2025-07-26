#include "gait_controller.h"
#include "leg.h"
#include <Arduino.h>
#include <algorithm>

void GaitController::update()
{
    unsigned long now = millis();            // Get current time in milliseconds
    float dt = (now - lastUpdate) / 1000.0f; // Convert milliseconds to seconds
    lastUpdate = now;                        // Update lastUpdate to current time

    float gaitFrequency = speed + 1.5f; // Adjust gait frequency based on speed
    for (int i = 0; i < 4; i++)
    {
        float offset = (i == 1 || i == 2) ? 0.5f : 0.0f; // Offset for legs 1 and 2
        phase[i] += gaitFrequency * dt;
        phase[i] = fmod(phase[i], 1.0f); // Keep phase in [0, 1)
    }
}

float bezier(float t, float p0, float p1, float p2, float p3)
{
    float u = 1 - t;
    return u * u * u * p0 + 3 * u * u * t * p1 + 3 * u * t * t * p2 + t * t * t * p3;
}

Vec3 GaitController::getFootTarget(int legIndex) {
    float p = phase[legIndex]; // Phase: 0.0 to 1.0
    float strideLength = 60.0f;
    float liftHeight = 30.0f;
    float groundHeight = -150.0f;

    Vec3 target;

    if (p < 0.5f) {
        // Swing phase: move foot forward and lift
        float swingPhase = p / 0.5f; // normalize [0, 1]
        target.x = -strideLength / 2 + strideLength * swingPhase; // from -30 to +30
        target.z = groundHeight + liftHeight * sin(PI * swingPhase); // smooth arc up and down
    } else {
        // Stance phase: move foot back on ground
        float stancePhase = (p - 0.5f) / 0.5f; // normalize [0, 1]
        target.x = strideLength / 2 - strideLength * stancePhase; // from +30 to -30
        target.z = groundHeight; // foot stays on ground
    }

    target.y = 0.0f;
    return target;
}
