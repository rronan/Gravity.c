#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define NBODIES 35

int WIDTH = 828;
int HEIGHT = 828;

GLFWwindow* setupWindow() {
    if (!glfwInit()) {
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
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, 0.0, 1.0);
    return window;
}

struct Body {
    double x;
    double y;
    double vx;
};

struct Space {
    struct Body* bodies[NBODIES];
} space;

void printSpace(struct Space* space){
    printf("++++++++++\n");
    printf("%p\n", space->bodies);
    for (int i = 0; i < NBODIES; i++) {
        printf("%p\n", space->bodies[i]);
        printf("%f\n", space->bodies[i]->x);
        printf("%f\n", space->bodies[i]->y);
        printf("%f\n", space->bodies[i]->vx);
        printf("***\n");
    }
    printf("----------\n");
}

void drawSpace(GLFWwindow* window){
    glClear(GL_COLOR_BUFFER_BIT);
    printf("foo\n");
    glfwSwapBuffers(window);
    glfwPollEvents();
    printf("bar\n");
}

void setSpace(struct Space* space){
    printf("%ld\n", sizeof(struct Body*));
    printf("%ld\n", sizeof(long));
    printf("assignment starts\n");
    for (int i = 0; i < NBODIES; i++) {
        /* space->bodies[i] = malloc(sizeof(struct Body*)); */
        printf("%ld\n", sizeof(space->bodies[i]));
        space->bodies[i] = malloc(sizeof(struct Body));
        space->bodies[i]->x = i;
        space->bodies[i]->y = 0;
        space->bodies[i]->vx = 0;
    }
    printf("assignment done\n");
}

int main() {
    GLFWwindow* window = setupWindow();
    setSpace(&space);
    while(!glfwWindowShouldClose(window)) {
        drawSpace(window);
        printSpace(&space);
        sleep(1);
    }
    glfwTerminate();
    return 1;
}

