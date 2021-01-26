#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

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
    double vy;
    double mass;
    int radius;
};

struct Space {
    struct Body body;
} space;

void printSpace(struct Space* space){
    printf("++++++++++\n");
    printf("%f\n", space->body.x);
    printf("%f\n", space->body.y);
    printf("%f\n", space->body.vx);
    printf("%f\n", space->body.vy);
    printf("%f\n", space->body.mass);
    printf("%d\n", space->body.radius);
    printf("----------\n");
}

void drawSpace(GLFWwindow* window, struct Space* space){
    glClear(GL_COLOR_BUFFER_BIT);
    printSpace(space);
    glfwSwapBuffers(window);
    printf("foo\n");
    glfwPollEvents();
    printf("bar\n");
}

void setSpace(struct Space* space){
    space->body.x = WIDTH / 2;
    space->body.y = HEIGHT / 2;
    space->body.vx = 0;
    space->body.vy = 0;
    space->body.mass = 10e3;
    space->body.radius = (int)((3. / 4.) / 3.142 * pow(10e3, 1. / 3.));
}

int main() {
    GLFWwindow* window = setupWindow();
    setSpace(&space);
    while(!glfwWindowShouldClose(window)) {
        printSpace(&space);
        drawSpace(window, &space);
        sleep(1);
    }
    glfwTerminate();
    return 1;
    }

