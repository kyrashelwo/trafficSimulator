 /* 
  * Class that specifies what a vehicle is.
  * super-class of eg car, truck, ect.
  */
#include "vehicle.hpp"
#include "pointerException.hpp"

Vehicle::Vehicle(double length, double width, double maxAcc, double maxSpeed, double laneChangeTime, Driver driver, double velocity, Lane *lane, double position) :
    mDriver(driver),
    mLength(length),
    mWidth(width),
    mMaxAcc(maxAcc),
    mMaxSpeed(maxSpeed),
    mLaneChangeTime(laneChangeTime)
{
    mVel = velocity;
    mpLane = lane;
    mPosition = position;
}


Vehicle::~Vehicle() {
    // std::cout << "deleting vehicle at "<< mPosition << " with speed " << mVel << std::endl;
    /* nothing to be done here */
}

void Vehicle::accelerate(double time, double distance, double velDiff) {
    double acc;


    // abort if there is no driver linked to this car.
    // if (mpDriver == 0) {
    //     acc = 0;
    //     std::cout << "acc: " << acc << std::endl;
    //     return;
    // }
    acc = mDriver.chooseAcceleration(time, mVel, distance, velDiff);
    // std::cout << "vel: " << mVel << " distance: " << distance << " velDiff: " << velDiff << std::endl;
    // std::cout << mPosition << " accelerates with " << acc << std::endl;

    acc = std::min(acc, mMaxAcc);
    acc = std::max(acc, -mMaxAcc);
    mVel += acc*time;
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
    if (mPosition >= 600)
        mPosition -= 600;
}

void Vehicle::shift(double shift) {
    mPosition += shift;
}

// void Vehicle::setDriver(Driver driver) {
//     mDriver = driver;
// }
