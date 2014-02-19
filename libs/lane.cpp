#include "lane.hpp"

Lane::Lane() {
    mpRoot = NULL;
}

Lane::~Lane() {
    // Delete all list elements and the corresponding vehicles.
    vehicleList *h = mpRoot;
    vehicleList *tmp;
    while (h != NULL) {
        tmp = h->next;

        // delete vehicle.
        delete h->current;

        // delete ListElement.
        delete h;
        h = tmp;
    }
}

void Lane::deleteVehicle(Vehicle *vehicle) {
    vehicleList *h = mpRoot;
    vehicleList *tmp;

    while (h != NULL)
        if (h->current == vehicle) {
            tmp = h->next;
            // delete vehicle
            delete h->current;

            // delete ListElement
            delete h;

            // repair connetivity
            
            
        }
            

}

bool Lane::vehicleFits(Vehicle *vehicle) {
    /* check if in the list adjaconed vehicles are far enough away. */
    vehicleList *h = mpRoot;
    while (h != NULL && h->next != 0 && h->next->current->getPos() < vehicle->getPos()) {
        h = h->next;
    }

    return true;
}

void Lane::addVehicle(Vehicle *vehicle) {
    vehicleList *h = mpRoot;
    vehicleList *tmp;
    
    if (vehicleFits(vehicle)) {

        // is it the first vehicle?
        if (h == NULL) {
            mpRoot = new vehicleList;
            mpRoot->current = vehicle;
            mpRoot->previous = NULL;
            mpRoot->next = NULL;
            vehicle->setLane(this);
            return;
        }
        while(h->next != NULL && h->next->current->getPos() < vehicle->getPos()) 
            h = h->next;

        tmp = h->next;
        h->next = new vehicleList;
        h->next->previous = h;
        h->next->current = vehicle;
        h->next->next = tmp;

        // if list not at its end connect next element to inserted one
        if (tmp != NULL) {
            tmp->previous = h->next;
        }
        vehicle->setLane(this);
    }
}

void Lane::print(bool full) {
    vehicleList *h = mpRoot;
    std::cout << "--- lane --- " << std::endl;
    while (h != NULL) {
        h->current->print(full);
        h = h->next;
    }
}

