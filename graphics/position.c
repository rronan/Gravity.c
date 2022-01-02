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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Gravity", NULL, NULL);
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
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, 0.0, 1.0);
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

void drawShip(struct Ship* ship) {
    drawBody(&ship->body);
    glBegin(GL_POLYGON);
    glVertex2f(ship->body.x - ship->body.radius * ship->ax, ship->body.y);
    glVertex2f(ship->body.x - 16 * ship->body.radius * ship->ax, ship->body.y -  8 * ship->body.radius);
    glVertex2f(ship->body.x - 16 * ship->body.radius * ship->ax, ship->body.y +  8 * ship->body.radius);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(ship->body.x, ship->body.y - ship->body.radius * ship->ay);
    glVertex2f(ship->body.x - 8 * ship->body.radius, ship->body.y - 16 * ship->body.radius * ship->ay);
    glVertex2f(ship->body.x + 8 * ship->body.radius, ship->body.y - 16 * ship->body.radius * ship->ay);
    glEnd();
}

void drawSpace(GLFWwindow* window, struct Space* space){
    glClear(GL_COLOR_BUFFER_BIT);
    for (unsigned long i = 0; i < NBODIES; i++) {
        drawBody(space->bodies[i]);
    };
    if (space->ship->exists == 1) drawShip(space->ship);
    glfwSwapBuffers(window);
    glfwPollEvents();
}
