#include "libs/lane.hpp"
#include "libs/car.hpp"

using namespace std;

int main(int argc, char** args) {
    // check usage.
    if (argc != 4) {
        cout << "Usage: trafficSimulator <vel> <distance> <velDiff>" << endl;
        return 0;
    }

    Driver *dConservative = new Driver(50, 120, 1, 0.1);
    Lane l1 = Lane();
    Lane l2 = Lane();
    Car *c1 = new Car(dConservative, 3, NULL, 0);
    l1.addVehicle(c1);
    Car *c2 = new Car(dConservative, 8, NULL, 6);
    l1.addVehicle(c2);
    Car *c3 = new Car(dConservative, 1.5, NULL, 3);
    l1.addVehicle(c3);
    l1.print();

    /* c1->print();
     * cout << l1.getLeaderDist(c1) << " , " << l1.getLeaderVelDiff(c1) << endl;

     * c2->print();
     * cout << l1.getLeaderDist(c3) << " , " << l1.getLeaderVelDiff(c2) << endl;

     * c3->print();
     * cout << l1.getLeaderDist(c3) << " , " << l1.getLeaderVelDiff(c3) << endl;
     */

    cout << "new acceleration: " << dConservative->chooseAcceleration(atoi(args[1]), atoi(args[2]), atoi(args[3])) << endl;

    // l1.moveVehicles(0.1);
    // l1.print();

}
