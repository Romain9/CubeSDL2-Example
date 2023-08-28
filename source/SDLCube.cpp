#include <iostream>
#include "../header/SDLCube.hpp"



SDLCube::SDLCube() {
    pts.insert(pts.begin(), {  // On place le cube au centre
        {540.0f, 260.0f, 260.0f}, {540.0f, 460.0f, 260.0f}, {740.0f, 260.0f, 260.0f}, {740.0f, 460.0f, 260.0f},
        {540.0f, 260.0f, 460.0f}, {540.0f, 460.0f, 460.0f}, {740.0f, 260.0f, 460.0f}, {740.0f, 460.0f, 460.0f}
    });
    
    center = {640.0f, 360.0f, 360.0f}; // Centre de rotation/Centre du cube

    // On initialize les matrices de rotation

    makeRotationX(rotMatX);
    makeRotationY(rotMatY);
    makeRotationZ(rotMatZ);
}

void SDLCube::makeRotationX(float (&mat)[][3]) {
    mat[0][0] = 1.0f;
    mat[0][1] = 0.0f;
    mat[0][2] = 0.0f;
    mat[0][3] = 0.0f;
    mat[1][0] = 0.0f;
    mat[1][1] = SDL_cosf(THETA);
    mat[1][2] = SDL_sinf(THETA); 
    mat[1][3] = 0.0f;
    mat[2][0] = 0.0f;
    mat[2][1] = -SDL_sinf(THETA);
    mat[2][2] = SDL_cosf(THETA);
    mat[2][3] = 0.0f;
    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
}

void SDLCube::makeRotationY(float (&mat)[][3]) {
    mat[0][0] = SDL_cosf(THETA);
    mat[0][1] = 0.0f;
    mat[0][2] = SDL_sinf(THETA);
    mat[0][3] = 0.0f;
    mat[1][0] = 0.0f;
    mat[1][1] = 1.0f;
    mat[1][2] = 0.0f;
    mat[1][3] = 0.0f;
    mat[2][0] = -SDL_sinf(THETA);
    mat[2][1] = 0.0f;
    mat[2][2] = SDL_cosf(THETA);
    mat[2][3] = 0.0f;
    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
}

void SDLCube::makeRotationZ(float (&mat)[][3]) {
    mat[0][0] = SDL_cosf(THETA);
    mat[0][1] = -SDL_sinf(THETA);
    mat[0][2] = 0.0f;
    mat[0][3] = 0.0f;
    mat[1][0] = SDL_sinf(THETA);
    mat[1][1] = SDL_cosf(THETA);
    mat[1][2] = 0.0f;
    mat[1][3] = 0.0f;
    mat[2][0] = 0.0f;
    mat[2][1] = 0.0f;
    mat[2][2] = 1.0f;
    mat[2][3] = 0.0f;
    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
}

void SDLCube::applyRotX(std::vector<point> &points) {
    float b,c;
    for (point &p : points) { // Pour chaque type de rotation on soustrait le centre du cube pour le "définir" comme centre de rotation
        b = (p.x - center.x) * rotMatX[1][0] + (p.y - center.y) * rotMatX[1][1] + (p.z - center.z) * rotMatX[1][2];
        c = (p.x - center.x) * rotMatX[2][0] + (p.y - center.y) * rotMatX[2][1] + (p.z - center.z) * rotMatX[2][2];

        p.y = center.y + b;
        p.z = center.z + c;
        /*
            Pas besoin de modifier le point 
            dans l'axe de la rotation (ici x).
            C'est une sorte de pivot, 
            donc ça valeur n'est pas modifiée
        */ 
            

    }
}

void SDLCube::applyRotY(std::vector<point> &points) {
    float a,c;
    for (point &p : points) {
        a = (p.x - center.x) * rotMatY[0][0] + (p.y - center.y) * rotMatY[0][1] + (p.z - center.z) * rotMatY[0][2];
        c = (p.x - center.x) * rotMatY[2][0] + (p.y - center.y) * rotMatY[2][1] + (p.z - center.z) * rotMatY[2][2];

        p.x = center.x + a;
        p.z = center.z + c;

    }
}

void SDLCube::applyRotZ(std::vector<point> &points) {
    float a,b;
    for (point &p : points) {
        a = (p.x - center.x) * rotMatZ[0][0] + (p.y - center.y) * rotMatZ[0][1] + (p.z - center.z) * rotMatZ[0][2];
        b = (p.x - center.x) * rotMatZ[1][0] + (p.y - center.y) * rotMatZ[1][1] + (p.z - center.z) * rotMatZ[1][2];

        p.x = center.x + a;
        p.y = center.y + b;
            
    }
}

void SDLCube::update() {
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);

    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    
    // On applique la rotation à tous les points à chaque frame
    applyRotX(pts);
    applyRotY(pts);
    applyRotZ(pts);

    
    // On relie les points à l'arrache

    SDL_RenderDrawLineF(r, pts.at(0).x, pts.at(0).y, pts.at(1).x, pts.at(1).y);
    SDL_RenderDrawLineF(r, pts.at(0).x, pts.at(0).y, pts.at(2).x, pts.at(2).y);
    SDL_RenderDrawLineF(r, pts.at(0).x, pts.at(0).y, pts.at(4).x, pts.at(4).y);
    
    SDL_RenderDrawLineF(r, pts.at(1).x, pts.at(1).y, pts.at(3).x, pts.at(3).y);
    SDL_RenderDrawLineF(r, pts.at(1).x, pts.at(1).y, pts.at(5).x, pts.at(5).y);
    
    SDL_RenderDrawLineF(r, pts.at(2).x, pts.at(2).y, pts.at(3).x, pts.at(3).y);
    SDL_RenderDrawLineF(r, pts.at(2).x, pts.at(2).y, pts.at(6).x, pts.at(6).y);
    
    SDL_RenderDrawLineF(r, pts.at(3).x, pts.at(3).y, pts.at(7).x, pts.at(7).y);
    
    SDL_RenderDrawLineF(r, pts.at(4).x, pts.at(4).y, pts.at(5).x, pts.at(5).y);
    SDL_RenderDrawLineF(r, pts.at(4).x, pts.at(4).y, pts.at(6).x, pts.at(6).y);
    
    SDL_RenderDrawLineF(r, pts.at(5).x, pts.at(5).y, pts.at(7).x, pts.at(7).y);
    
    SDL_RenderDrawLineF(r, pts.at(6).x, pts.at(6).y, pts.at(7).x, pts.at(7).y);
    
    SDL_RenderPresent(r);
}

/**     Mini cours de trigo     **/
/*

    Le cosinus et le sinus représente le changement dans l'abscisse et l'ordonnée,
    ils determinent de combien le point se place sur leurs axes respectifs pendant la rotation.

*/