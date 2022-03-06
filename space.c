#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include "headers/space.h"
#include <time.h>

const double R = 200;
const double V = 100;
const double G = 1e5;
const double DT = 1e-4;

void setSpace(struct Space* space){
    srand (time(NULL));
    double avg_vx = 0;
    double avg_vy = 0;
    double avg_vz = 0;
    int i = 0;
    while (i < NBODIES) {
        double x = (rand() * 2 - 1) * R / (double)RAND_MAX;
        double y = (rand() * 2 - 1) * R / (double)RAND_MAX;
        /* double z = (rand() * 2 - 1) * R / (double)RAND_MAX; */
        double z = 0;
        double vx = (rand() * 2 - 1) * V / (double)RAND_MAX;
        double vy = (rand() * 2 - 1) * V / (double)RAND_MAX;
        /* double vz = (rand() * 2 - 1) * V / (double)RAND_MAX; */
        double vz = 0;
        if ((x * x + y * y + z * z) <= R * R) {
            space->bodies[i] = (struct Body*)malloc(sizeof(struct Body));
            space->bodies[i]->x = x;
            space->bodies[i]->y = y;
            space->bodies[i]->z = z;
            space->bodies[i]->vx = vx;
            space->bodies[i]->vy = vy;
            space->bodies[i]->vz = vz;
            space->bodies[i]->mass = 1;
            space->bodies[i]->radius = 5;
            avg_vx += vx;
            avg_vy += vy;
            avg_vz += vz;
            i++;
        }
    }
    for (i = 0; i < NBODIES; ++i) {
        space->bodies[i]->vx -= avg_vx / NBODIES;
        space->bodies[i]->vy -= avg_vy / NBODIES;
        space->bodies[i]->vz -= avg_vz / NBODIES;
    }
}
