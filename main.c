#include "headers/graphic.h"
#include "headers/physics.h"
#include "headers/space.h"
#include <stdio.h>

struct Space space;
struct Camera camera;

int main() {
    GLFWwindow* window = setupWindow();
    setSpace(&space);
    setCamera(&camera);
    int i = 0;
    while(!glfwWindowShouldClose(window)) {
        forwardPhysics(&space);
        i--;
        if (i < 0) {
            drawSpace(window, &space, &camera);
            i = 100;
        }
    }
    glfwTerminate();
    return 1;
}

