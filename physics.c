#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "headers/space.h"

void applyGravitation(struct Body* a, struct Body* b) {
    double px = pow(a->x - b->x, 2);
    double py = pow(a->y - b->y, 2);
    double pp = pow(px + py, 2);
    a->vx = a->vx + DT * copysign(G * b->mass * px / pp, b->x - a->x);
    a->vy = a->vy + DT * copysign(G * b->mass * py / pp, b->y - a->y);
}

void updatePosition(struct Body* a) {
    a->x = a->x + DT * a->vx;
    a->y = a->y + DT * a->vy;
}

void updatePhysics(struct Space* space){
    for (unsigned long i = 0; i < NBODIES; i++) {
        if (space->ship->exists == 1) {
            applyGravitation(&space->ship->body, space->bodies[i]);
        }
        for (unsigned long j = 0; j < NBODIES; j++) {
            if (i != j) {
                applyGravitation(space->bodies[i], space->bodies[j]);
            }
        }
        updatePosition(space->bodies[i]);
    };
    if (space->ship->exists == 1) {
        space->ship->body.vx = space->ship->body.vx + DT * space->ship->ax * POWER;
        space->ship->body.vy = space->ship->body.vy + DT * space->ship->ay * POWER;
        updatePosition(&space->ship->body);
    }
}
