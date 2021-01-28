#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "headers/space.h"


const int WIDTH = 828;
const int HEIGHT = 828;
const double G = 1e3;
const double DT = 1e-7;
const double POWER = 5e3;

void setSpaceReal(struct Space* space){
    // define earth
    struct Body earth;
    earth.x = WIDTH / 2;
    earth.y = HEIGHT / 2;
    earth.vx = 0;
    earth.vy = 0;
    earth.mass = 1e4;
    earth.radius = (3. / 4.) / 3.142 * pow(earth.mass, 1. / 3.);
    space->bodies[0] = &earth;

    // define moon
    struct Body moon;
    moon.x = WIDTH / 2;
    moon.y = HEIGHT / 8;
    moon.vx = -100;
    moon.vy = 0;
    moon.mass = 0.012 * earth.mass;
    moon.radius = (3. / 4.) / 3.142 * pow(moon.mass, 1. / 3.);
    space->bodies[1] = &moon;

    // define ship
    struct Body body;
    body.x = earth.x + 50;
    body.y = earth.y;
    body.vx = 0;
    body.vy = -400;
    body.mass = 0;
    body.radius = moon.radius / 2;

    struct Ship ship;
    ship.ax = 0;
    ship.ay = 0;
    ship.exists = 1;
    ship.body = body;

    space->ship = &ship;
}
