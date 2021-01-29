#ifndef OPTIM_H
#define OPTIM_H

struct Variable;

struct Body;

double computeLossValue(struct Body* a, struct Body* b);

void computeLossGradient(struct Variable* pred, struct Body* target);

void forwardPhysics(struct Body* a);

void backwardPhysics(struct Body* a);

#endif
