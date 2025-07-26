#ifndef GAIT_CONTROLLER_H
#define GAIT_CONTROLLER_H

#include "Vec3.h"

class GaitController
{
public:
    void update();
    Vec3 getFootTarget(int legIndex);

    void setSpeed(float speed);
    void setDirection(float x, float y);

private:
    float phase[4];
    float speed = 0.25;
    float directionX = 1.0;
    float directionY = 0.0;

    unsigned long lastUpdate = 0;
};
#endif // GAIT_CONTROLLER_H