#ifndef PHYSICS_H
# define PHYSICS_H

void applyGravitation(struct Body*, struct Body*);

void updatePosition(struct Body*);

void updatePhysics(struct Space*);

#endif


