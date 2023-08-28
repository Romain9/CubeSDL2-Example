#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <unistd.h>

#include "header/SDLCube.hpp"

#define WIDTH 1280
#define HEIGHT 720


int main(int argv, char** args) { 
    SDLCube sC = SDLCube();

    SDL_Event e;
    

    while(true) { // Boucle du "jeu"
        
        
       sC.update();

        
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
        
    }

    return 0;
}
