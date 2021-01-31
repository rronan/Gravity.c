#ifndef SPACE_H
# define SPACE_H

extern const int WIDTH;

extern const int HEIGHT;

extern const double G;

extern const double DT;

extern const double POWER;

struct Body {
    double x;
    double y;
    double vx;
    double vy;
    double mass;
    double radius;
};

struct Ship {
    struct Body body;
    double ax;
    double ay;
    int exists;
};

struct Space {
    struct Body* bodies[NBODIES];
    struct Ship* ship;
};

void setSpace(struct Space*);

#endif


