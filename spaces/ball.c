#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/space.h"

const double R = 100;
const int HW = 1000;
const double G = 1e6;
const double DT = 3e-7;


void setSpace(struct Space* space){
    int i = 0;
    while (i < NBODIES) {
        double x = (rand() * 2 - 1) * R / (double)RAND_MAX;
        double y = (rand() * 2 - 1) * R / (double)RAND_MAX;
        double z = (rand() * 2 - 1) * R / (double)RAND_MAX;
        if ((x * x + y * y + z * z) <= R * R) {
            space->bodies[i] = (struct Body*)malloc(sizeof(struct Body));
            space->bodies[i]->x = x;
            space->bodies[i]->y = y;
            space->bodies[i]->z = z;
            space->bodies[i]->vx = 0;
            space->bodies[i]->vy = 0;
            space->bodies[i]->vz = 0;
            space->bodies[i]->mass = 1;
            space->bodies[i]->radius = 1;
            i++;
        }
    }
}
