#include "headers/command.h"
#include "headers/graphic.h"
#include "headers/physics.h"
#include "headers/space.h"

struct Space space;

int main() {
    init_keyboard();
    GLFWwindow* window = setupWindow();
    setSpace(&space);
    int i = 0;
    if (space.ship->exists) init_keyboard();
    while(!glfwWindowShouldClose(window)) {
        forwardPhysics(&space);
        i--;
        if (i < 0) {
            if (space.ship->exists) controlPower(&space);
            drawSpace(window, &space);
            i = 4000;
        }
    }
    glfwTerminate();
    if (space.ship->exists) close_keyboard();
    return 1;
}

