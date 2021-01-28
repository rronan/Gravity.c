#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "headers/space.h"


const int WIDTH = 828;
const int HEIGHT = 828;
const double G = 1e3;
const double DT = 1;
const double POWER = 5e3;

void setSpace(struct Space* space){
    space->bodies[0] = (struct Body*)malloc(sizeof(struct Body));
    space->bodies[0]->x = WIDTH / 2;
    space->bodies[0]->y = HEIGHT / 2;
    space->bodies[0]->vx = 0;
    space->bodies[0]->vy = 0;
    space->bodies[0]->radius = 10;
    space->ship = (struct Ship*)malloc(sizeof(struct Ship));
    space->ship->exists = 0;
}
