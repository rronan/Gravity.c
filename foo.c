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
};

struct Space {
    struct Body body;
} space;

void drawSpace(GLFWwindow* window){
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    printf("foo\n");
    glfwPollEvents();
    printf("bar\n");
}

void setSpace(struct Space* space){
    space->body.x = WIDTH / 2;
    space->body.y = HEIGHT / 2;
    space->body.vx = 0;
}

int main() {
    GLFWwindow* window = setupWindow();
    setSpace(&space);
    while(!glfwWindowShouldClose(window)) {
        printf("%f\n", space.body.x);
        drawSpace(window);
        sleep(1);
    }
    glfwTerminate();
    return 1;
    }

