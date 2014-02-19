#include "car.hpp"

Car::Car(double vel, Lane *lane, double position) : 
    Vehicle(4.5, 1.7, 4., 60., 3., vel, lane, position) {
    // nothing to be done so far ...
}

Car::~Car() { /* nothing to be done */} 

CarType Car::getTyp() {
    return CAR;
}
