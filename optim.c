#include <string.h>
#include <math.h>
#include "stack.c"

#define NBODIES 2

const int WIDTH = 828;
const int HEIGHT = 828;
const double DT = 1;
const double LR = 1e-3;
const double G = 1;
int NSTEPS = 10;
int NEPOCHS = 10000;

struct Body {
    double x;
    double y;
    double vx;
    double vy;
    double mass;
    double radius;
};

struct Variable{
    struct Body value;
    struct Body grad;
};

struct Space{
    struct Variable* variables[NBODIES];
}* space;

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

double computeLossValue(struct Space* space, struct Body* targets[NBODIES]){
    double loss = 0;
    for (int i=0; i<NBODIES; i++){
        double dx = space->variables[i]->value.x - targets[i]->x;
        double dy = space->variables[i]->value.y - targets[i]->y;
        loss += dx * dx + dy * dy;
    }
    return loss;
}

void computeLossGradient(struct Space* pred, struct Body* target[NBODIES]){
    for (int i=0; i<NBODIES; i++) {
        pred->variables[i]->grad.x = 2 * (pred->variables[i]->value.x - target[i]->x);
        pred->variables[i]->grad.y = 2 * (pred->variables[i]->value.y - target[i]->y);
        pred->variables[i]->grad.vx = 0;
        pred->variables[i]->grad.vy = 0;
        pred->variables[i]->grad.radius = 0;
        pred->variables[i]->grad.mass = 0;
    }
}

void forwardGravitation(struct Body* a, struct Body* b) {
    double px = pow(a->x - b->x, 2);
    double py = pow(a->y - b->y, 2);
    double pp = pow(px + py, 2);
    a->vx = a->vx + DT * copysign(G * b->mass * px / pp, b->x - a->x);
    a->vy = a->vy + DT * copysign(G * b->mass * py / pp, b->y - a->y);
}

void forwardPhysics(struct Space* space){
    for (int i=0; i<NBODIES; i++) {
        for (int j=0; j < NBODIES; j++) {
            if (i != j) forwardGravitation(&space->variables[i]->value, &space->variables[j]->value);
        }
        space->variables[i]->value.x += DT * space->variables[i]->value.vx;
        space->variables[i]->value.y += DT * space->variables[i]->value.vy;
    };
}

void backwardGravitation(struct Variable* a, struct Variable* b) {
    // g(f(x))' = g'(f(x))*f'(x)
    double px = pow(a->x - b->x, 2);
    double py = pow(a->y - b->y, 2);
    double pp = pow(px + py, 2);
    a->gradient->x = 
    a->vx = a->vx + DT * copysign(G * b->mass * px / pp, b->x - a->x);
    a->vy = a->vy + DT * copysign(G * b->mass * py / pp, b->y - a->y);
}

struct Space* backwardPhysics(struct Space* a, struct Space* b) {
    // g(f(x))' = g'(f(x))*f'(x)
    for (int i=0; i<NBODIES; i++) {
        for (int j=0; j < NBODIES; j++) {
            if (i != j) forwardGravitation(&space->variables[i]->value, &space->variables[j]->value);
        }
        space->variables[i]->value.x += DT * space->variables[i]->value.vx;
        space->variables[i]->value.y += DT * space->variables[i]->value.vy;
    };
    return a;
}

void learningStep(struct Space* space) {
    for (int i=0; i<NBODIES; i++) {
        space->variables[i]->value.x -= LR * space->variables[i]->grad.x;
        space->variables[i]->value.y -= LR * space->variables[i]->grad.y;
        space->variables[i]->value.vx -= LR * space->variables[i]->grad.vx;
        space->variables[i]->value.vy -= LR * space->variables[i]->grad.vy;
    }
}

int main() {
    struct Body* targets[NBODIES];
    targets[0] = &(struct Body){.x=WIDTH / 2, .y=0, .vx=0, .vy=0, .mass=0, .radius=0};
    targets[1] = &(struct Body){.x=WIDTH / 2, .y=0, .vx=0, .vy=0, .mass=0, .radius=0};
    space->variables[0] = &(struct Variable){
        .value = {.x=WIDTH * 0.9, .y=HEIGHT/2, .vx=-100, .vy=0, .mass=0, .radius=0},
        .grad = {.x=0, .y=0, .vx=0, .vy=0, .mass=0, .radius=0}
    };
    space->variables[1] = &(struct Variable){
        .value = {.x=WIDTH * 0.1, .y=HEIGHT/2, .vx=100, .vy=0, .mass=0, .radius=0},
        .grad = {.x=0, .y=0, .vx=0, .vy=0, .mass=0, .radius=0}
    };
    struct Stack* stack = NULL;
    for (int i=0; i<NEPOCHS; i++) {
        for (int j=0; j<NSTEPS; j++) {
            struct Space* cp = malloc(sizeof(struct Space));
            memcpy(cp, space, sizeof(struct Space));
            stack = push(&stack, cp);
            forwardPhysics(space);
        }
        double lossValue = computeLossValue(space, targets);
        printf("final loss: %lf\n", lossValue);
        computeLossGradient(space, targets);
        while (!isEmpty(stack)){
            space = backwardPhysics(pop(&stack), space);
        }
    }
    for (int i=0; i<NBODIES; i++) printVariable(space->variables[i]);
    return 1;
}

