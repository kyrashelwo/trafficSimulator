#include "driver.hpp"

Driver::Driver(double minComfortDist, double freeFlowVel, double comfortAcc, double accVariance, double reactionTime) :  
    mMinComfortDist(minComfortDist),
    mFreeFlowVel(freeFlowVel),
    mComfortAcc(comfortAcc),
    mAccVariance(accVariance),
    mReactionTime(reactionTime)
{
    mAccState = FREE_FLOW;
    mTimeUntilReaction = mReactionTime;

}

Driver::~Driver() { /* nothing to be done ... */ }

double Driver::chooseAcceleration(double time, double velocity, double distance, double velDiff) {
    distance -= mMinComfortDist;
    AcceleratingState desiredAccState;

    // if the car is too close, decelerate as hard as possible. #emergency break.
    if (distance <= 0)
        desiredAccState = EMERGENCY_BREAK;

    // if the distance is getting smaller decelerate depending on how far it is away.
    else if (velDiff < 0 && distance < 10 * mMinComfortDist)
        desiredAccState = BREAKING;

    // if the driver is slower than the man in front, go to mFreeFlowVel.
    else 
        desiredAccState = FREE_FLOW;

    // if we are not in the state we want to be: take accout for reaction time before chanaging state!
    if (desiredAccState != mAccState) {
        if (mTimeUntilReaction <= 0) {
            mAccState = desiredAccState;
            mTimeUntilReaction = mReactionTime;
        }
        mTimeUntilReaction -= time;
    } 

    if (mAccState == FREE_FLOW) {
        // accelerate until we hit disired free flow velocity mFreeFlowVel
        if (velocity <= mFreeFlowVel)
            return mComfortAcc;
        else
            return 0;
    }

    else if (mAccState == EMERGENCY_BREAK)
        return -1000;

    else 
        return -mComfortAcc;
}

Driver* Driver::copy() {
    return new Driver(mMinComfortDist, mFreeFlowVel, mComfortAcc, mAccVariance, mReactionTime);
}

bool Driver::changeLane(Lane *leftLane, Lane *currentLane, Lane *rightLane) const {
    // no multiLanes so far.
    return false;
}

// void Driver::setVehicle(Vehicle *newVehicle) {
    // mpVehicle = newVehicle;
// }
