 /* 
  * Class that specifies what a car is.
  */

#ifndef LIBS_CAR_HPP
#define LIBS_CAR_HPP

#include "vehicle.hpp"

class Car : public Vehicle {
private:
public:
    Car(double vel, Lane * lane, double position = 0);
    ~Car();
    CarType getTyp() override;
};

#endif // LIBS_CAR_HPP

