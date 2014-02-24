 /* 
  * Class that specifies what a vehicle is.
  * super-class of eg car, truck, ect.
  */

#ifndef LIBS_VEHICLE_HPP
#define LIBS_VEHICLE_HPP

#include <iostream>
#include <algorithm>

#include "driver.hpp"

class Driver;

class Lane;

enum CarType {CAR, TRUCK};

class Vehicle {
private:
    const Driver *mpDriver; // contains personality of driver. Determines when/how he accelerates/decelerates and when he switches lines.
    const double mLength; // Length of the vehicle.
    const double mWidth; // Width of the vehicle.
    const double mMaxAcc; // Maximum Acceleration possible for this vehicle (both throttle and break).
    const double mMaxSpeed; // Maximum possible speed this vehicle can reach.
    const double mLaneChangeTime; // Time needed to switch between two lanes.
    double mVel; // current speed of the vehicle.
    double mPosition; // current position of the vehicle.
    Lane *mpLane; // points to the lane, the car is currently driving on. 

public:
    Vehicle(double length, double width, double maxAcc, double maxSpeed, double laneChangeTime, Driver *driver, double vel, Lane *lane, double position = 0);
    virtual ~Vehicle();

    virtual CarType getTyp() = 0;

    double getLength() {return mLength;}
    double getWidth() {return mWidth;}
    double getVel() {return mVel;}
    double getPos() {return mPosition;}

    double getMaxAcc() {return mMaxAcc;}
    double getMaxSpeed() {return mMaxSpeed;}
    double getLaneChangeTime() {return mLaneChangeTime;}

    void setLane(Lane *lane);

    // sets the driver/personality that drives the car.
    void setDriver(Driver *driver);

    double distManInFront();
    double velDiffToManInFront();
    // double getMaxAcc() {return maxAcc;}
    void accelerate(double time, double distance, double velDiff);
    void move(double time);
    void print(bool full = false);
};

#endif // LIBS_VEHICLE_HPP
