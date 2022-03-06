#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "headers/space.h"
#include <stdio.h>

void forwardGravitation(struct Body* a, struct Body* b) {
    double px = pow(a->x - b->x, 2);
    double py = pow(a->y - b->y, 2);
    double pz = pow(a->z - b->z, 2);
    double r = pow(px + py + pz, .5);
    double f = G * b->mass / (r * r);
    a->vx = a->vx + DT * f * (b->x - a->x) / r;
    a->vy = a->vy + DT * f * (b->y - a->y) / r;
    a->vz = a->vz + DT * f * (b->z - a->z) / r;
}

void forwardPhysics(struct Space* space){
    for (unsigned long i = 0; i < NBODIES; i++) {
        for (unsigned long j = 0; j < NBODIES; j++) {
            if (i != j) {
                forwardGravitation(space->bodies[i], space->bodies[j]);
            }
        }
        space->bodies[i]->x += DT * space->bodies[i]->vx;
        space->bodies[i]->y += DT * space->bodies[i]->vy;
        space->bodies[i]->z += DT * space->bodies[i]->vz;
    };
}
