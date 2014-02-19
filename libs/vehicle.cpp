 /* 
  * Class that specifies what a vehicle is.
  * super-class of eg car, truck, ect.
  */
#include "vehicle.hpp"

    
Vehicle::Vehicle(double length, double width, double maxAcc, double maxSpeed, double laneChangeTime,double velocity, Lane *lane, double position) :
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


Vehicle::~Vehicle() { /* nothing to be done here */}

void Vehicle::accelerate(double acc, double t) {
    acc = std::min(acc, mMaxAcc);
    acc = std::max(acc, -mMaxAcc);
    mVel += acc*t;
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
