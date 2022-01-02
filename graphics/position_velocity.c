#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "../headers/space.h"
#include "../headers/graphic.h"

GLFWwindow* setupWindow() {
    if(!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return 0;
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(2 * WIDTH, HEIGHT, "Gravity", NULL, NULL);
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
    glOrtho(0.0, 2 * WIDTH, 0.0, HEIGHT, 0.0, 1.0);
    return window;
}

void drawBody(struct Body* body){
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 20; i++) {
        glVertex2f(
            body->x + (body->radius * cos(i * 2 * 3.142 / 20)),
            body->y + (body->radius * sin(i * 2 * 3.142 / 20))
        );
    }
    glEnd();
}

void drawBodyVelocity(struct Body* body){
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 20; i++) {
        glVertex2f(
            WIDTH * 3 / 2 + body->vx / 4 + (body->radius * cos(i * 2 * 3.142 / 20)),
            HEIGHT / 2 + body->vy / 4 + (body->radius * sin(i * 2 * 3.142 / 20))
        );
    }
    glEnd();
}

void drawSpace(GLFWwindow* window, struct Space* space){
    for (unsigned long i = 0; i < NBODIES; i++) {
        drawBody(space->bodies[i]);
        drawBodyVelocity(space->bodies[i]);
    };
    glfwSwapBuffers(window);
    glfwPollEvents();
}
