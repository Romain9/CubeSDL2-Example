#ifndef SDLCube

#include <vector>

#include "SDLWin.hpp"

#define THETA 0.002f

struct point {
    float x;
    float y;
    float z;

    bool operator!=(const point& p2) {
        return (this->x != p2.x || this->y != p2.y || this->z != p2.z);
    }
};

class SDLCube : SDLWin {
private:
    std::vector<point> pts;
    point center;
    float rotMatX[3][3];
    float rotMatY[3][3];
    float rotMatZ[3][3];

    
public:
    SDLCube();

    void makeRotationX(float (&mat)[][3]);

    void makeRotationY(float (&mat)[][3]);

    void makeRotationZ(float (&mat)[][3]);

    void applyRotX(std::vector<point> &points);

    void applyRotY(std::vector<point> &points);

    void applyRotZ(std::vector<point> &points);

    void update();

};

#endif // !SDLCube