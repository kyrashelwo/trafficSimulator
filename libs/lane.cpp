#include "lane.hpp"

Lane::Lane() {
    mpRoot = NULL;
}

Lane::~Lane() {
    // Delete all list elements and the corresponding vehicles.
    VehicleList *h = mpRoot;
    VehicleList *tmp;
    while (h != NULL) {
        tmp = h->next;

        // delete vehicle.
        if (h->current != 0)
        delete h->current;

        // delete ListElement.
        delete h;
        h = tmp;
    }
}

Lane::VehicleList* Lane::findVehicleEntry(Vehicle *vehicle) {
    VehicleList *h = mpRoot;

    // check if the given vehicle exists at all
    if (vehicle == NULL)
        throw PointerException("findVehicleEntry", "Vehicle *vehicle");

    while (h != NULL) {
        if (h->current == vehicle) {
            return h;
        }
        h = h->next;
    }

    return NULL;
}

bool Lane::deleteVehicle(Vehicle *vehicle) {
    VehicleList *h = NULL;
    VehicleList *storeNext;
    VehicleList *storePrev;

    // check if the given vehicle exists at all
    if (vehicle == NULL)
        throw PointerException("deleteVehicle", "Vehicle *vehicle");

    h = findVehicleEntry(vehicle);

    if (h != NULL) {
        storeNext = h->next;
        storePrev = h->previous;
        // std::cout << "next: " << storeNext;
        // std::cout << " / prev: " << storePrev << std::endl;

        // exclude element which will be deleted from list.

        // if the deleted element is the first one set the new root.
        // else make sure, that the previous element links to the correct element after deletion.
        if (storePrev == NULL) {
            mpRoot = storeNext;
            if (storeNext != NULL)
                storeNext->previous = NULL;
        }
        else if (storeNext == NULL)
            storePrev->next = 0;
        else {
            storePrev->next = storeNext;
            storeNext->previous = storePrev;
        }

        // delete vehicle
        std::cout << "delete: " << h->current << std::endl;
        delete h->current;
        h->current = NULL;


        // delete ListElement
        h->next = NULL; // prevent destructor from deleting whole list.
        delete h;

        return true;
    }
    return false;
}

bool Lane::vehicleFits(Vehicle *vehicle) {
    /* check if in the list adjaconed vehicles are far enough away. */
    VehicleList *h = mpRoot;

    // check if the given vehicle exists at all;


    if (vehicle == NULL)
        throw PointerException("deleteFits", "Vehicle *vehicle");

    while (h != NULL && h->next != 0 && h->next->current->getPos() < vehicle->getPos()) {
        h = h->next;
    }

    return true;
    // TODO actually check, wheter there is enough space to change lanes.
}

void Lane::addVehicle(Vehicle *vehicle) {
    // check if the given vehicle exists at all;
    if (vehicle == NULL)
        throw PointerException("addVehicle", "Vehicle *vehicle");

    VehicleList *h = mpRoot;
    VehicleList *tmp;

    if (vehicleFits(vehicle)) {
        // is it the first vehicle?
        if (h == NULL) {
            mpRoot = new VehicleList;
            mpRoot->current = vehicle;
            mpRoot->previous = NULL;
            mpRoot->next = NULL;
            vehicle->setLane(this);
            return;
        }

        // sort the vehicle at the right position
        while (h->next != NULL && h->next->current->getPos() < vehicle->getPos()) {
            h = h->next;
        }

        // insert vehicle in list
        tmp = h->next;
        h->next = new VehicleList;
        h->next->previous = h;
        h->next->current = vehicle;
        h->next->next = tmp;

        // if list not at its end connect next element to inserted one
        if (tmp != NULL) {
            tmp->previous = h->next;
        }
        vehicle->setLane(this);
    } else {
        // TODO maybe return false here?
    }
}

void Lane::print(bool full) {
    VehicleList *h = mpRoot;
    std::cout << "--- lane --- " << std::endl;
    while (h != NULL) {
        std::cout << "vehicle at adress " << h << " prev/next " << h->previous << "/" << h->next << std::endl;
        h->current->print(full);
        h = h->next;
    }
}


Vehicle* Lane::getLeadingVehicle(Vehicle* vehicle) {
    VehicleList *vehicleListEntry = findVehicleEntry(vehicle);
    // if the vehicle was not found, or there is no leading vehicle, return NULL.
    if (vehicleListEntry == NULL || vehicleListEntry->next == NULL)
        return NULL;
    return vehicleListEntry->next->current;
}

Vehicle* Lane::getFollowingVehicle(Vehicle* vehicle) {
    VehicleList *vehicleListEntry = findVehicleEntry(vehicle);
    // if the vehicle was not found, or there is no leading vehicle, return NULL.
    if (vehicleListEntry == NULL || vehicleListEntry->previous == NULL)
        return NULL;
    return vehicleListEntry->previous->current;
}

void Lane::moveVehicles(double time) {
    VehicleList *h = mpRoot;
    while (h != NULL) {
        h->current->move(time);
        h = h->next;
    }
}

double Lane::getLeaderDist(Vehicle *vehicle) {
    Vehicle *leader = getLeadingVehicle(vehicle);
    if (leader) {
        return leader->getPos() - vehicle->getPos();
    }
    else {
        // if there is no leader, return a huge value.
        return INFINITY;
    }
}

double Lane::getLeaderVelDiff(Vehicle *vehicle) {
    Vehicle *leader = getLeadingVehicle(vehicle);
    if (leader) {
        return leader->getVel() - vehicle->getVel();
    }
    else {
        // if there is no leader, return 0.
        return INFINITY;
    }
}

void Lane::accelerateVehicles(double time) {
    VehicleList *h = mpRoot;
    while (h != NULL) {
        h->current->accelerate(time, getLeaderDist(h->current), getLeaderVelDiff(h->current));
        h = h->next;
    }
}

void Lane::initLeapfrog(double time) {
    accelerateVehicles(time/2);
}

void Lane::leapfrog(double time) {
    moveVehicles(time);
    accelerateVehicles(time);
}

void Lane::draw(SDL_Renderer* pRenderer) {
    SDL_Rect car;
    SDL_Rect stateRect;
    car.x = 0;
    car.y = 0;
    car.w = 0;
    car.h = 2;

    stateRect.w = 10;
    stateRect.h = 5;
    int offsetY = 100;
    VehicleList *h = mpRoot;
    while (h != NULL) {
        car.x = h->current->getPos() * mToPixel;
        car.y = offsetY;
        car.w = h->current->getLength() * mToPixel;
        car.h = 2 * mToPixel;

        SDL_SetRenderDrawColor( pRenderer, 0, 0, 0, 255 );

        SDL_RenderFillRect( pRenderer, &car );

        // draw a small rectangle indicating the current state of the driver.
        stateRect.x = car.x;
        stateRect.y = car.y;
        SDL_SetRenderDrawColor(pRenderer,
                r[h->current->getAccState()], 
                g[h->current->getAccState()], 
                0,
                255);
        SDL_RenderFillRect(pRenderer, &stateRect);
        h = h->next;

    }
}


void Lane::shift(double shiftVelocity, double time) {
    VehicleList *h = mpRoot;
    while (h != NULL) {
        h->current->shift(- shiftVelocity * time);
        h = h->next;
    }
}

void Lane::followVehicle(Vehicle *vehicle, double time) {
    shift(vehicle->getVel(), time);
}

const int Lane::mToPixel= 4;
