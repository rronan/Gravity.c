#include <string.h>
#include "headers/command.h"
#include "headers/graphic.h"
#include "headers/space.h"
#include "stack.c"

#define NSTEPS 10

const int WIDTH = 828;
const int HEIGHT = 828;
const double G = 1e3;
const double DT = 1;
const double POWER = 5e3;

struct Variable{
    struct Body value;
    struct Body grad;
};

void printBody(struct Body body){
    printf("    x: %lf\n", body.x);
    printf("    y: %lf\n", body.y);
    printf("    vx: %lf\n", body.vx);
    printf("    vy: %lf\n", body.vy);
    printf("    mass: %lf\n", body.mass);
    printf("    radius: %lf\n", body.radius);
}


void printVariable(struct Variable* variable){
    printf("++++++++\n");
    printf("variable pointer: %p\n", variable);
    printf("value:\n");
    printBody(variable->value);
    printf("gradient:\n");
    printBody(variable->grad);
    printf("--------\n");
}

double computeLossValue(struct Body* a, struct Body* b){
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    double dvx = a->vx - b->vx;
    double dvy = a->vy - b->vy;
    return dx * dx + dy * dy + dvx * dvx + dvy * dvy;
}

void computeLossGradient(struct Variable* pred, struct Body* target){
    pred->grad.x = 2 * (pred->value.x - target->x);
    pred->grad.y = 2 * (pred->value.y - target->y);
    pred->grad.x = 2 * (pred->value.vx - target->vx);
    pred->grad.x = 2 * (pred->value.vy - target->vy);
    pred->grad.radius = 0;
    pred->grad.mass = 0;
}

void forwardPhysics(struct Variable* a) {
    a->value.x += DT * a->value.vx;
    a->value.y += DT * a->value.vy;
}

void backwardPhysics(struct Body* a) {
    a->x = a->x + DT * a->vx;
    a->y = a->y + DT * a->vy;
}


int main() {
    struct Body target = {
        .x = 0,
        .y = 0,
        .vx = -100,
        .vy = -100,
        .mass = 0,
        .radius = 0,
    };
    struct Variable variable = {
        .value = {.x=HEIGHT/2, .y=WIDTH/2, .vx=0, .vy=-10, .mass=0, .radius=0},
        .grad = {.x=0, .y=0, .vx=0, .vy=0, .mass=0, .radius=0}
    };
    struct Stack* stack = newStack(&variable);
    for (int i=0; i < NSTEPS; i++) {
        forwardPhysics(&variable);
        struct Variable* copy_pointer = malloc(sizeof(struct Variable));
        memcpy(copy_pointer, &variable, sizeof(struct Variable));
        push(&stack, copy_pointer);
        printVariable(&variable);
    }
    double lossValue = computeLossValue(&variable.value, &target);
    printf("final loss: %lf\n", lossValue);
    computeLossGradient(&variable, &target);
    printVariable(&variable);
    return 1;
}

