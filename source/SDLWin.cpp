#include "../header/SDLWin.hpp"


SDLWin::SDLWin() {
        w = SDL_CreateWindow("SDL_Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280.0f, 720.0f, 0);
        r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
        
        // On modifie la couleur en noir (de base en blanc)
        SDL_RenderClear(r);
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderPresent(r); // On montre les changements
    
    }

SDLWin::~SDLWin() {
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
        
    }

SDL_Renderer* SDLWin::getRenderer() {
        return r;
}

