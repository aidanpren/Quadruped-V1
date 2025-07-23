#ifndef IKCONTROLLER_H
#define IKCONTROLLER_H

struct JointAngles {
    float j1;
    float j2;
    float j3;
};

class IKController {
    public:
        IKController(float l1, float l2, float l3);
        JointAngles calculateIK(float x, float y, float z);
        void moveTo(float x, float y, float z);

        float l1 = 40.6; // Length of the first link
        float l2 = 130.0; // Length of the second link
        float l3 = 140.0; // Length of the third link

};

#endif // for safety
