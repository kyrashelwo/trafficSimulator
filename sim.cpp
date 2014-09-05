#include "libs/lane.hpp"
#include "libs/car.hpp"
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, char** args) {
    const double dt = 0.05;
    const double simulationSpeedup = 10;
    // check usage.
    if (argc != 4) {
        cout << "Usage: trafficSimulator <vel> <distance> <velDiff>" << endl;
        return 0;
    }

    // initialize prototypes of the driver personalities.
    Driver *dConservative = new Driver(50, 120, 1, 0.1, 0.2);
    Driver *dAgressive = new Driver(2, 160, 4, 0.1, 0.2);

    // initialize lane
    Lane l1 = Lane();
    Car *c0 = new Car(*dAgressive, 4, &l1, -20);
    l1.addVehicle(c0);
    Car *c1 = new Car(*dAgressive, 4, &l1, 20);
    l1.addVehicle(c1);
    Car *c2 = new Car(*dAgressive, 2, NULL, 60);
    l1.addVehicle(c2);
    Car *c3 = new Car(*dConservative, 1, NULL, 100);
    l1.addVehicle(c3);
    l1.initLeapfrog(dt);

    /// open window
    SDL_Window* pWindow = NULL;

    pWindow = SDL_CreateWindow("Traffic Simulation", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1000,
            200,
            SDL_WINDOW_SHOWN);

    if (pWindow == NULL)
        return 0;

    // Setup renderer
    SDL_Renderer* pRenderer = NULL;
    pRenderer =  SDL_CreateRenderer( pWindow, 0, SDL_RENDERER_ACCELERATED);

    if (pRenderer == 0)
        return 0;

    for(int i=0; i < 1000; i++) {

        // Set render color to white. 
        SDL_SetRenderDrawColor( pRenderer, 200, 200, 200, 255 );

        // Clear winow
        SDL_RenderClear( pRenderer );

        // Render rect
        // SDL_RenderFillRect( pRenderer, &r );
        l1.draw(pRenderer);

        // Render the rect to the screen
        SDL_RenderPresent(pRenderer);

        // Wait for 5 sec
        SDL_Delay(1000 * dt/ simulationSpeedup);

        // do a leapfrog step
        l1.leapfrog(dt);

        // shift the lane to keep track of vehicles
        l1.followVehicle(c3,dt);

    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}
