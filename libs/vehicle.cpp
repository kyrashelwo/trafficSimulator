 /* 
  * Class that specifies what a vehicle is.
  * super-class of eg car, truck, ect.
  */
#include "vehicle.hpp"
#include "pointerException.hpp"

Vehicle::Vehicle(double length, double width, double maxAcc, double maxSpeed, double laneChangeTime, Driver *driver, double velocity, Lane *lane, double position) :
    mpDriver(driver),
    mLength(length),
    mWidth(width),
    mMaxAcc(maxAcc),
    mMaxSpeed(maxSpeed),
    mLaneChangeTime(laneChangeTime)
{
    mVel = velocity;
    mpLane = lane;
    mPosition = position;
    mAccState = FREE_FLOW;
}


Vehicle::~Vehicle() {
    // std::cout << "deleting vehicle at "<< mPosition << " with speed " << mVel << std::endl;
    /* nothing to be done here */
}

void Vehicle::accelerate(double t, double distance, double velDiff) {
    double acc;


    // abort if there is no driver linked to this car.
    if (mpDriver == 0) {
        acc = 0;
        std::cout << "acc: " << acc << std::endl;
        return;
    }
    acc = mpDriver->chooseAcceleration(this, distance, velDiff);

    acc = std::min(acc, mMaxAcc);
    acc = std::max(acc, -mMaxAcc);
    mVel += acc*t;
    mVel = std::max(mVel, 0.);
}

void Vehicle::setLane(Lane *lane) {
    mpLane = lane;
}

void Vehicle::print(bool full) {
    if (full) {
        std::cout << "--- vehicle ---" << std::endl;
        std::cout << "carType:" << getTyp() << std::endl;
        std::cout << "size: " << getWidth() << " x " << getLength() << std::endl;
        std::cout << "maxAcc: " << getMaxAcc() << std::endl;
        std::cout << "maxSpeed: " << getMaxSpeed() << std::endl;
        std::cout << "LaneChangeTime: " << getLaneChangeTime() << std::endl;
        std::cout << "Adress to lane: " << mpLane << std::endl;
    }
    std::cout << "pos: " << getPos() << " vel: " << getVel() << std::endl;
}

void Vehicle::move(double time) {
    mPosition += mVel*time;
}

void Vehicle::setDriver(Driver *driver) {
    if (mpDriver == NULL)
        throw PointerException("Vehicle::setDriver","Driver *driver");
    mpDriver = driver;
}
