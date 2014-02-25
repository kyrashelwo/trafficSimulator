 /*
  * Class that specifies what a driver is.
  */

#ifndef LIBS_DRIVER_HPP
#define LIBS_DRIVER_HPP

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
    double mComfortAcc;

    // random variance in acceleration. Contains also error of deltaV expectation.
    double mAccVariance;

public:
    Driver(double minComfortDist, double freeFlowVel, double comfortAcc, double accVariance);
    virtual ~Driver();

    // choose how much to accelerate depending on current traffic situation.
    // distance = distance to next car in front of this one
    // velDiff = vCar - vThis
    virtual double chooseAcceleration(double velocity, double distance, double velDiff) const;

    // choose if the lane should be changed depending on current traffic situation.
    // TODO returns always FALSE sofar.
    virtual bool changeLane(Lane *leftLane, Lane *rightLane) const;

    // correlates the driver to a new Vehicle.
    // not needed, since one personality can control many cars ...
    // void setVehicle(Vehicle *newVehicle);
};

#endif // LIBS_DRIVER_HPP

