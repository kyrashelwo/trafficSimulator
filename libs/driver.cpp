#include "driver.hpp"

Driver::Driver(double minComfortDist, double freeFlowVel, double comfortAcc, double accVariance) {
    mMinComfortDist = minComfortDist;
    mFreeFlowVel = freeFlowVel;
    mComfortAcc = comfortAcc;
    mAccVariance = accVariance;
}

Driver::~Driver() {}

double Driver::chooseAcceleration(double velocity, double distance, double velDiff) const {
    distance -= mMinComfortDist;

    // if the car is too close, decelerate as hard as possible.
    if (distance <= 0)
        return -1000;

    // if the distance is getting smaller decelerate depending on how far it is away.
    if (velDiff < 0) {
        // if the driver is faster than is man in front, break.
        return (2 * velocity + velDiff) * velDiff / (2 * distance);
    } else {
        // if the driver is slower than the man in front, go to mFreeFlowVel.
        return (mFreeFlowVel - velocity) / mFreeFlowVel * mComfortAcc;
    }
}

bool Driver::changeLane(Lane *leftLane, Lane *rightLane) const {
    // no multiLanes so far.
    return false;
}

// void Driver::setVehicle(Vehicle *newVehicle) {
    // mpVehicle = newVehicle;
// }
