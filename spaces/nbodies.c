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


void setSpace(struct Space* space){
    for (int i = 0; i < NBODIES; i++) {
        double a = (int)(i - NBODIES / 2);
        space->bodies[i] = (struct Body*)malloc(sizeof(struct Body));
        space->bodies[i]->x = WIDTH * (double)(i + 1) / (NBODIES + 1);
        space->bodies[i]->y = HEIGHT / 2;
        space->bodies[i]->vx = 0;
        space->bodies[i]->vy = a * 60;
        space->bodies[i]->mass = 5e3;
        space->bodies[i]->radius = (3. / 4.) / 3.142 * pow(10e3, 1. / 3.);
    }
    space->ship = (struct Ship*)malloc(sizeof(struct Ship));
    space->ship->exists=0;
}
