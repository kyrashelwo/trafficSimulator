 /* 
  * Class that specifies what a vehicle is.
  * super-class of eg car, truck, ect.
  */

#ifndef LIBS_DRIVER_HPP
#define LIBS_DRIVER_HPP

#include "vehicle.hpp"

class Lane;

class Driver {
private:
    // minimal Distance at which this driver feels comfortable.
    double mMinComfortDist;

    // variance of the expected velocityDifference. 
    // double mVelExpectationVariance;

    // Speed which the driver wants to reach
    double mFreeFlowVel;

    // maximal acceleration which is comfortable for this driver.
    double mMaxComfortAcc;

    // random variance in acceleration. Contains also error of deltaV expectation.
    double mAccVariance;

    Vehicle *mpVehicle;

public:
    Driver(double minComfortDist, double freeFlowVel, double maxComfortAcc, double accVariance, Vehicle *newVehicle);
    virtual ~Driver();

    // choose how much to accelerate depending on current traffic situation.
    // distance = distance to next car in front of this one
    // velDiff = vCar - vThis
    virtual double chooseAcceleration(double distance, double velDiff);

    // choose if the lane should be changed depending on current traffic situation.
    // TODO returns always FALSE sofar.
    virtual bool changeLane(Lane *leftLane, Lane *rightLane);

    // correlates the driver to a new Vehicle.
    void setVehicle(Vehicle *newVehicle);
};

#endif // LIBS_DRIVER_HPP

