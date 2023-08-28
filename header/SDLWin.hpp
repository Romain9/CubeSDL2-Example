#ifndef SDLWin

#include <SDL2/SDL.h>

class SDLWin { // Classe pour initialiser la fenêtre SDL2 
protected:
    SDL_Window *w;
    SDL_Renderer *r;

public:
    SDLWin();

    ~SDLWin();
    
    SDL_Renderer *getRenderer();
};
#endif // !SDLWin