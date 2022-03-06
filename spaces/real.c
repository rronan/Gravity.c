#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "../headers/space.h"

const int WIDTH = 828;
const int HEIGHT = 828;
const double G = 1e3;
const double DT = 1e-7;
const double POWER = 5e3;

void setSpaceReal(struct Space* space){
    struct Body earth;
    earth.x = WIDTH / 2;
    earth.y = HEIGHT / 2;
    earth.z = 0;
    earth.vx = 0;
    earth.vy = 0;
    earth.vz = 0;
    earth.mass = 1e4;
    earth.radius = (3. / 4.) / 3.142 * pow(earth.mass, 1. / 3.);
    space->bodies[0] = &earth;

    struct Body moon;
    moon.x = WIDTH / 2;
    moon.y = HEIGHT / 8;
    moon.z = 0;
    moon.vx = -100;
    moon.vy = 0;
    moon.vz = 0;
    moon.mass = 0.012 * earth.mass;
    moon.radius = (3. / 4.) / 3.142 * pow(moon.mass, 1. / 3.);
    space->bodies[1] = &moon;
}
