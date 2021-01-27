#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef GRAPHIC_H
# define GRAPHIC_H

struct Body;
struct Ship;
struct Space;

GLFWwindow* setupWindow();

void drawBody(struct Body*);

void drawShip(struct Ship*);

void drawSpace(GLFWwindow*, struct Space*);

#endif


