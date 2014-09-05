 /*
  * Class that specifies what a driver is.
  */

#ifndef LIBS_DRIVER_HPP
#define LIBS_DRIVER_HPP

class Lane;

// type for managing different states the driver might be in.
enum AcceleratingState {
    FREE_FLOW = 0,
    BREAKING,
    EMERGENCY_BREAK,
    NUM_ACCELERATION_STATES
};


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

    // current acceleration state of the driver
    AcceleratingState mAccState;

    // keep track of the time, that has passed since the reaction is desired
    double mTimeUntilReaction;

public:
    Driver(double minComfortDist, double freeFlowVel, double comfortAcc, double accVariance, double mReactionTime);
    virtual ~Driver();

    // create a new Driver on the heap (make sure to delete it at some point...
    virtual Driver* copy();

    // choose how much to accelerate depending on current traffic situation.
    // distance = distance to next car in front of this one
    // velDiff = vCar - vThis
    virtual double chooseAcceleration(double time, double velocity, double distance, double velDiff);

    // choose if the lane should be changed depending on current traffic situation.
    // TODO returns always FALSE sofar.
    virtual bool changeLane(Lane *leftLane, Lane *currentLane, Lane *rightLane) const;

    virtual AcceleratingState getAccState() const {return mAccState;}; 

    // correlates the driver to a new Vehicle.
    // not needed, since one personality can control many cars ...
    // void setVehicle(Vehicle *newVehicle);
};

#endif // LIBS_DRIVER_HPP
