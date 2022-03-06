#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef GRAPHIC_H
# define GRAPHIC_H

struct Body;
struct Space;
struct Camera {
    double hw;
    /* double translation[3]; */
    /* double rotation[3][3]; */
};

GLFWwindow* setupWindow();

void drawBody(struct Body*, struct Camera*);

void drawSpace(GLFWwindow*, struct Space*, struct Camera*);

void setCamera(struct Camera* camera);

#endif


