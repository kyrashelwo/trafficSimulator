 /*
  * Class that specifies what a driver is.
  */

#ifndef LIBS_DRIVER_HPP
#define LIBS_DRIVER_HPP


class Lane;
class Vehicle;

enum AcceleratingState {FREE_FLOW, ACCELERATING, BREAKING, EMERGENCY_BREAK};

class Driver {
private:
    // minimal Distance at which this driver feels comfortable.
    const double mMinComfortDist;

    // variance of the expected velocityDifference. 
    // double mVelExpectationVariance;

    // Speed which the driver wants to reach
    const double mFreeFlowVel;

    // maximal acceleration which is comfortable for this driver.
    const double mComfortAcc;

    // random variance in acceleration. Contains also error of deltaV expectation.
    const double mAccVariance;

    // reaction time of this driver 
    const double mReactionTime;

public:
    Driver(double minComfortDist, double freeFlowVel, double comfortAcc, double accVariance, double mReactionTime);
    virtual ~Driver();

    // choose how much to accelerate depending on current traffic situation.
    // distance = distance to next car in front of this one
    // velDiff = vCar - vThis
    virtual double chooseAcceleration(Vehicle *vehicle, double distance, double velDiff) const;

    // choose if the lane should be changed depending on current traffic situation.
    // TODO returns always FALSE sofar.
    virtual bool changeLane(Lane *leftLane, Lane *currentLane, Lane *rightLane) const;

    // correlates the driver to a new Vehicle.
    // not needed, since one personality can control many cars ...
    // void setVehicle(Vehicle *newVehicle);
};

#endif // LIBS_DRIVER_HPP

