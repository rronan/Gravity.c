#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "headers/space.h"

void forwardGravitation(struct Body* a, struct Body* b) {
    double px = pow(a->x - b->x, 2);
    double py = pow(a->y - b->y, 2);
    double pp = pow(px + py, 2);
    a->vx = a->vx + DT * copysign(G * b->mass * px / pp, b->x - a->x);
    a->vy = a->vy + DT * copysign(G * b->mass * py / pp, b->y - a->y);
}

void forwardPhysics(struct Space* space){
    for (unsigned long i = 0; i < NBODIES; i++) {
        if (space->ship->exists == 1) {
            forwardGravitation(&space->ship->body, space->bodies[i]);
        }
        for (unsigned long j = 0; j < NBODIES; j++) {
            if (i != j) {
                forwardGravitation(space->bodies[i], space->bodies[j]);
            }
        }
        space->bodies[i]->x += DT * space->bodies[i]->vx;
        space->bodies[i]->y += DT * space->bodies[i]->vy;
    };
    if (space->ship->exists == 1) {
        space->ship->body.vx = space->ship->body.vx + DT * space->ship->ax * POWER;
        space->ship->body.vy = space->ship->body.vy + DT * space->ship->ay * POWER;
        space->ship->body.x += DT * space->ship->body.vx;
        space->ship->body.y += DT * space->ship->body.vy;
    }
}
