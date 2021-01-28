#include "headers/command.h"
#include "headers/graphic.h"
#include "headers/physics.h"
#include "headers/space.h"


struct Space space;

void forward(struct Space* space) {
}

int main() {
    setSpace(&space);
    while (1){
        updatePhysics(&space);
    }
    glfwTerminate();
    return 1;
}

