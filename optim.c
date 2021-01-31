#include <string.h>
#include "headers/command.h"
#include "headers/graphic.h"
#include "headers/space.h"
#include "stack.c"


const int WIDTH = 828;
const int HEIGHT = 828;
const double DT = 0.1;
const double LR = 1e-3;
int NSTEPS = 100;
int NEPOCHS = 10000;

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
    pred->grad.vx = 2 * (pred->value.vx - target->vx);
    pred->grad.vy = 2 * (pred->value.vy - target->vy);
    pred->grad.radius = 0;
    pred->grad.mass = 0;
}

void forwardPhysics(struct Variable* a) {
    a->value.x += DT * a->value.vx;
    a->value.y += DT * a->value.vy;
}

struct Variable* backwardPhysics(struct Variable* a, struct Variable* b) {
    // g(f(x))' = g'(f(x))*f'(x)
    a->grad.x = b->grad.x + b->grad.vx * DT;
    a->grad.y = b->grad.y + b->grad.vy * DT;
    a->grad.vx = b->grad.vx;
    a->grad.vy = b->grad.vy;
    a->grad.radius = b->grad.radius;
    a->grad.mass = b->grad.mass;
    return a;
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
    struct Variable* variable = &(struct Variable){
        .value = {.x=HEIGHT/2, .y=WIDTH/2, .vx=0, .vy=-10, .mass=0, .radius=0},
        .grad = {.x=0, .y=0, .vx=0, .vy=0, .mass=0, .radius=0}
    };
    struct Stack* stack = NULL;
    for (int i=0; i<NEPOCHS; i++) {
        for (int j=0; j<NSTEPS; j++) {
            struct Variable* cp = malloc(sizeof(struct Variable));
            memcpy(cp, variable, sizeof(struct Variable));
            stack = push(&stack, cp);
            forwardPhysics(variable);
        }
        double lossValue = computeLossValue(&variable->value, &target);
        printf("final loss: %lf\r", lossValue);
        computeLossGradient(variable, &target);
        while (!isEmpty(stack)) {
            variable = backwardPhysics(pop(&stack), variable);
        }
        variable->value.x -= LR * variable->grad.x;
        variable->value.y -= LR * variable->grad.y;
        variable->value.vx -= LR * variable->grad.vx;
        variable->value.vy -= LR * variable->grad.vy;
    }
    printf("\n");
    printVariable(variable);
    return 1;
}

