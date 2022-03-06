#ifndef SPACE_H
# define SPACE_H

#define NBODIES 3

extern const double G;
extern const double DT;
extern const double POWER;

struct Body {
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
    double mass;
    double radius;
};

struct Space {
    struct Body* bodies[NBODIES];
};

void setSpace(struct Space*);

#endif


