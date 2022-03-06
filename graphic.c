#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "headers/space.h"
#include "headers/graphic.h"


GLFWwindow* setupWindow() {
    if(!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return 0;
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 800, "Gravity", NULL, NULL);
    if (!window) {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    GLint framebufferWidth = 0, framebufferHeight = 0;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);
    glMatrixMode(GL_PROJECTION);
    return window;
}

void drawBody(struct Body* body, struct Camera* camera){
    glLoadIdentity();
    glOrtho(-camera->hw, camera->hw, -camera->hw, camera->hw, -1, 1e6);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 8; i++) {
        glVertex2f(
            body->x + (body->radius * cos(i * 2 * 3.142 / 8)),
            body->y + (body->radius * sin(i * 2 * 3.142 / 8))
        );
    }
    glEnd();
}

void drawSpace(GLFWwindow* window, struct Space* space, struct Camera* camera){
    glClear(GL_COLOR_BUFFER_BIT);
    for (unsigned long i = 0; i < NBODIES; i++) {
        drawBody(space->bodies[i], camera);
    };
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void setCamera(struct Camera* camera) {
    camera->hw = 400.0;
    /* camera->translation = {0, 0, 0}; */
    /* camera->rotation = { */
    /*     {1, 0, 0}, */
    /*     {0, 1, 0}, */
    /*     {0, 0, 1} */
    /* }; */
}
