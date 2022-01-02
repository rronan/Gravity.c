#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "../headers/space.h"

const int WIDTH = 600;
const int HEIGHT = 600;
const double G = 1e3;
const double DT = 3e-6;
const double POWER = 5e3;


void setSpace(struct Space* space){
    // define earth
    space->bodies[0] = (struct Body*)malloc(sizeof(struct Body));
    space->bodies[0]->x = WIDTH / 2;
    space->bodies[0]->y = HEIGHT / 2;
    space->bodies[0]->vx = 0;
    space->bodies[0]->vy = 0;
    space->bodies[0]->mass = 1e4;
    space->bodies[0]->radius = (3. / 4.) / 3.142 * pow(1e4, 1. / 3.);

    // define moon
    space->bodies[1] = (struct Body*)malloc(sizeof(struct Body));
    space->bodies[1]->x = WIDTH / 2;
    space->bodies[1]->y = 7 * (HEIGHT / 16);
    space->bodies[1]->vx = -400;
    space->bodies[1]->vy = 0;
    space->bodies[1]->mass = 0.001;
    space->bodies[1]->radius = space->bodies[0]->radius / 10;

    space->ship = (struct Ship*)malloc(sizeof(struct Ship));
    space->ship->exists=0;
}
