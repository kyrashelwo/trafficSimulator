#ifndef LIBS_LANE_HPP
#define LIBS_LANE_HPP

#include "vehicle.hpp"
#include <list>

class Lane {
private:
    struct vehicleList {
        Vehicle *current;
        vehicleList *next;
        vehicleList *previous;
    };

    vehicleList *mpRoot;


public:
    // create a new (empty) lane.
    Lane();

    // destroy a lane. don't forget to delete also all vehicles in this lane.
    ~Lane();

    // adds a new vehicle to the Lan
    void addVehicle(Vehicle *vehicle);

    // deletes an existing vehicle.
    void deleteVehicle(Vehicle *vehicle);

    // returns wheter a vehicle fits into the defined place on this lane (true) or not (false)
    bool vehicleFits(Vehicle *vehicle);

    // prints a list of all vehicles in the list on the standard output
    void print(bool full = false);

};

#endif // LIBS_LANE_HPP
