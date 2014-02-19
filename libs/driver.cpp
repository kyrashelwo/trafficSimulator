 /* 
  * Class that specifies what a vehicle is.
  * super-class of eg car, truck, ect.
  */
/*
#ifndef LIBS_DRIVER_HPP
#define LIBS_DRIVER_HPP

class Lane;

class Driver {
private:
    // minimal Distance at which this driver feels comfortable.
    double mMinComfortDist;

    // minimal difference in veloicity that this driver can detect.
    double mVelocityExp;

    // maximal acceleration which is comfortable for this driver.
    double mMaxComfortAcc;

    // random variance in acceleration
    double mAccVariance;

public:
    Driver(double minComfortDist, double mVelExpectationVariance, double maxComfortAcc, double accVariance);
    virtual ~Driver();

    // choose how much to accelerate depending on current traffic situation.
    virtual double chooseAcceleration(double distance, double velDiff);

    // choose if the lane should be changed depending on current traffic situation.
    virtual bool changeLane(Lane *leftLane, Lane *rightLane);
};
#endif // LIBS_DRIVER_HPP
*/
#include "driver.hpp"

Driver::Driver(double minComfortDist, double freeFlowVel, double maxComfortAcc, double accVariance, Vehicle *newVehicle = 0) {
    mMinComfortDist = minComfortDist;
    mFreeFlowVel = freeFlowVel;
    mMaxComfortAcc = maxComfortAcc;
    mAccVariance = accVariance;
    mpVehicle = newVehicle;
}

Driver::~Driver() {}

double Driver::chooseAcceleration(double distance, double velDiff) {
    double startSpeed = mpVehicle->getVel();
    distance -= mMinComfortDist;
    if (velDiff < 0) {
        // if the driver is faster than is man in front, break.
        return (startSpeed - velDiff) * velDiff/ distance / 2;
    } else {
        // if the driver is slower than the man in front, go to mFreeFlowVel.
        return (startSpeed - mFreeFlowVel) / mFreeFlowVel * mMaxComfortAcc;
    }
}

bool Driver::changeLane(Lane *leftLane, Lane *rightLane) {
    // no multiLanes so far.
    return false;
}


void Driver::setVehicle(Vehicle *newVehicle) {
    mpVehicle = newVehicle;
}
