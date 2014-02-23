#include "libs/lane.hpp"
#include "libs/car.hpp"

using namespace std;

int main() {
    Lane l1 = Lane();
    Lane l2 = Lane();
    Car *c1 = new Car(3, NULL, 0);
    l1.addVehicle(c1);
    Car *c2 = new Car(8, NULL, 6);
    l1.addVehicle(c2);
    Car *c3 = new Car(1.5, NULL, 3);
    l1.addVehicle(c3);
    l1.print();

    try {
        l1.deleteVehicle(c2);
    }
    catch (PointerException &e) {
        cout << e.getString() << endl;

    }

    l1.print();
    l1.deleteVehicle(c1);
    l1.print();
    l1.deleteVehicle(c3);
    l1.print();

}
