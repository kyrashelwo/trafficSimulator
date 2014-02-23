#ifndef LIBS_LANE_HPP
#define LIBS_LANE_HPP

#include "vehicle.hpp"
#include "pointerException.hpp"
#include <list>

class Lane {
private:
    struct VehicleList {
        Vehicle *current;
        VehicleList *next;
        VehicleList *previous;
    };

    VehicleList *mpRoot;

    VehicleList* findVehicleEntry(Vehicle *vehicle);

    VehicleList* getPreviousVehicle (VehicleList *current) {
        if (current !=0)
            throw PointerException("getPreviousVehicle", "VehicleList *current");
        else
            return current->next;
    };

    VehicleList* getNextVehicle (VehicleList *current) {
        if (current !=0)
            throw PointerException("getPreviousVehicle", "VehicleList *current");
        else
            return current->previous;
    }

    VehicleList* getRoot() {return mpRoot;}

public:
    // create a new (empty) lane.
    Lane();

    // destroy a lane. don't forget to delete also all vehicles in this lane.
    ~Lane();

    // adds a new vehicle to the Lan
    void addVehicle(Vehicle *vehicle);

    // deletes an existing vehicle and returns true, if sucessful.
    bool deleteVehicle(Vehicle *vehicle);

    // returns wheter a vehicle fits into the defined place on this lane (true) or not (false)
    bool vehicleFits(Vehicle *vehicle);

    // prints a list of all vehicles in the list on the standard output
    void print(bool full = false);

    Vehicle* getLeadingVehicle(Vehicle* vehicle);
};

#endif // LIBS_LANE_HPP
