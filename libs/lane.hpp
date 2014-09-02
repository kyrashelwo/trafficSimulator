#ifndef LIBS_LANE_HPP
#define LIBS_LANE_HPP

#include "vehicle.hpp"
#include "pointerException.hpp"
#include <list>
#include <SDL2/SDL.h>

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

    static const int mToPixel;

public:
    // create a new (empty) lane.
    Lane();

    // destroy a lane. don't forget to delete also all vehicles in this lane.
    ~Lane();

    // adds a new vehicle to the lane.
    void addVehicle(Vehicle *vehicle);

    // deletes an existing vehicle and returns true, if sucessful.
    bool deleteVehicle(Vehicle *vehicle);

    // returns wheter a vehicle fits into the defined place on this lane (true) or not (false)
    bool vehicleFits(Vehicle *vehicle);

    // moves all Vehicles in this lane with their current speed for the specified time.
    void moveVehicles(double time);

    // return distance to leading vehicle.
    double getLeaderDist(Vehicle *vehicle);

    // return velocity difference to leading vehicle.
    double getLeaderVelDiff(Vehicle *vehicle);

    // update the accelerations of all vehicles in this lane.
    void accelerateVehicles(double time);

    // prints a list of all vehicles in the list on the standard output
    void print(bool full = false);

    // initiallizes the velocity to be inbetween two time-steps
    void initLeapfrog(double time);

    // integrates the system for the time 'time' with a leapfrog algorithm. Acceleartions are derived from the driver ai.
    void leapfrog(double time); 

    Vehicle* getLeadingVehicle(Vehicle* vehicle);
    Vehicle* getFollowingVehicle(Vehicle* vehicle);

    // draw the lane on the current renderer
    void draw(SDL_Renderer* pRenderer);

    // scale distances from meter to pixel
};



#endif // LIBS_LANE_HPP
