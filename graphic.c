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
    GLFWwindow* window = glfwCreateWindow(HW, HW, "Gravity", NULL, NULL);
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
    glLoadIdentity();
    // see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
    glOrtho(-HW/2, HW/2, -HW/2, HW/2, -HW/2, HW/2);
    return window;
}

void drawBody(struct Body* body){
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 8; i++) {
        glVertex2f(
            body->x + (body->radius * cos(i * 2 * 3.142 / 8)),
            body->y + (body->radius * sin(i * 2 * 3.142 / 8))
        );
    }
    glEnd();
}

void drawSpace(GLFWwindow* window, struct Space* space){
    glClear(GL_COLOR_BUFFER_BIT);
    for (unsigned long i = 0; i < NBODIES; i++) {
        drawBody(space->bodies[i]);
    };
    glfwSwapBuffers(window);
    glfwPollEvents();
}
