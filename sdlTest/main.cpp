#include <string>
#include <iostream>
#include <SDL2/SDL.h>

int main (int argc, char** argv) {
    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        600,
        600,
        SDL_WINDOW_SHOWN);

    // Setup renderer
    SDL_Renderer* pRenderer = NULL;
    pRenderer =  SDL_CreateRenderer( pWindow, 0, SDL_RENDERER_ACCELERATED);

    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect r;
    r.w = 20;
    r.h = 20;

    for(int i=0; i < 1000; i++) {
        r.x = 50+i % 600 + i/600 * 100;
        r.y = i % 600 - r.h;


        // Set render color to red. 
        SDL_SetRenderDrawColor( pRenderer, 0, 255, 0, 255 );

        // Clear winow
        SDL_RenderClear( pRenderer );

        SDL_SetRenderDrawColor( pRenderer, 255, 0, 0, 255 );



        // Render rect
        SDL_RenderFillRect( pRenderer, &r );

        // Render the rect to the screen
        SDL_RenderPresent(pRenderer);

        // Wait for 5 sec
        SDL_Delay( 1 );
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return EXIT_SUCCESS;
}
