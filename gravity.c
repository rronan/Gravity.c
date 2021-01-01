#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <unistd.h>
#include <termios.h>

int WIDTH = 828;
int HEIGHT = 828;
float G = 1e3;
double DT = 1e-5;
double POWER = 5e3;

static struct termios initial_settings, new_settings;
static int peek_character = -1;

void init_keyboard() {
    tcgetattr(0, &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard() {
    tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit() {
    unsigned char ch;
    int nread;
    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1) {
        peek_character = ch;
        return 1;
    }
    return 0;
}

int readch() {
    char ch;
    if (peek_character != -1) {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0, &ch, 1);
    return ch;
}

GLFWwindow* setupWindow() {
    GLFWwindow* window;
    if(!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
    return 0;
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow( WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL );
    if (!window) {
	fprintf( stderr, "Failed to open GLFW window\n" );
	glfwTerminate();
    return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    GLint framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, 0.0, 1.0);
    return window;
}

struct Body {
    double x;
    double y;
    double vx;
    double vy;
    double mass;
    double radius;
};

void drawBody(struct Body body){
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 20; i++) {
        glVertex2f(
            body.x + (body.radius * cos(i * 2 * 3.142 / 20)),
            body.y + (body.radius * sin(i * 2 * 3.142 / 20))
        );
    }
    glEnd();
}

struct Ship {
    struct Body body;
    double ax;
    double ay;
};

void drawShip(struct Ship ship) {
    drawBody(ship.body);
    glBegin(GL_POLYGON);
    glVertex2f(ship.body.x - ship.body.radius * ship.ax, ship.body.y);
    glVertex2f(ship.body.x - 16 * ship.body.radius * ship.ax, ship.body.y -  8 * ship.body.radius);
    glVertex2f(ship.body.x - 16 * ship.body.radius * ship.ax, ship.body.y +  8 * ship.body.radius);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(ship.body.x, ship.body.y - ship.body.radius * ship.ay);
    glVertex2f(ship.body.x - 8 * ship.body.radius, ship.body.y - 16 * ship.body.radius * ship.ay);
    glVertex2f(ship.body.x + 8 * ship.body.radius, ship.body.y - 16 * ship.body.radius * ship.ay);
    glEnd();
}

struct Space {
    struct Body bodies[2];
    struct Ship ship;
};

void drawSpace(GLFWwindow* window, struct Space space){
    glClear(GL_COLOR_BUFFER_BIT);
    for (unsigned long i = 0; i < (sizeof(space.bodies)/sizeof(struct Body)); i++) {
        drawBody(space.bodies[i]);
    };
    drawShip(space.ship);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

struct Body applyGravitation(struct Body a, struct Body b) {
    double px = pow(a.x - b.x, 2);
    double py = pow(a.y - b.y, 2);
    double pp = pow(px + py, 2);
    a.vx = a.vx + DT * copysign(G * b.mass * px / pp, b.x - a.x);
    a.vy = a.vy + DT * copysign(G * b.mass * py / pp, b.y - a.y);
    return a;
}

struct Body updatePosition(struct Body a) {
    a.x = a.x + DT * a.vx;
    a.y = a.y + DT * a.vy;
    return a;
}

struct Space controlPower(struct Space space) {
    if (kbhit() == 1) {
        switch (readch()) {
            case 'f':
                space.ship.ax = 1;
                printf("right\n");
                break;
            case 's':
                space.ship.ax = -1;
                printf("left\n");
                break;
            case 'e':
                space.ship.ay = 1;
                printf("up\n");
                break;
            case 'd':
                space.ship.ay = -1;
                printf("down\n");
                break;
        }
        fflush(stdout);
    } else {
        space.ship.ax = 0;
        space.ship.ay = 0;
    }
    return space;
}

struct Space updatePhysics(struct Space space){
    unsigned long nBodies = (sizeof(space.bodies)/sizeof(struct Body));
    for (unsigned long i = 0; i < nBodies; i++) {
        space.ship.body = applyGravitation(space.ship.body, space.bodies[i]);
        for (unsigned long j = 0; j < nBodies; j++) {
            if (i != j) {
                space.bodies[i] = applyGravitation(space.bodies[i], space.bodies[j]);
            }
        }
        space.bodies[i] = updatePosition(space.bodies[i]);
    };
    space.ship.body.vx = space.ship.body.vx + DT * space.ship.ax * POWER;
    space.ship.body.vy = space.ship.body.vy + DT * space.ship.ay * POWER;
    space.ship.body = updatePosition(space.ship.body);
    return space;
}

struct Space setupSpace(void){
    // define earth
    struct Body earth;
    earth.x = WIDTH / 2;
    earth.y = HEIGHT / 2;
    earth.vx = 0;
    earth.vy = 0;
    earth.mass = 1e4;
    earth.radius = (3. / 4.) / 3.142 * pow(earth.mass, 1. / 3.);

    // define moon
    struct Body moon;
    moon.x = WIDTH / 2;
    moon.y = HEIGHT / 8;
    moon.vx = -100;
    moon.vy = 0;
    moon.mass = 0.012 * earth.mass;
    moon.radius = (3. / 4.) / 3.142 * pow(moon.mass, 1. / 3.);

    // define ship
    struct Ship ship;
    ship.body.x = earth.x + 50;
    ship.body.y = earth.y;
    ship.body.vx = 0;
    ship.body.vy = -400;
    ship.body.mass = 0;
    ship.body.radius = moon.radius / 2;
    ship.ax = 0;
    ship.ay = 0;

    // define space
    struct Space space;
    space.bodies[0] = earth;
    space.bodies[1] = moon;
    space.ship = ship;

    return space;
}

int main() {
    init_keyboard();
    GLFWwindow* window = setupWindow();
    struct Space space = setupSpace();
    int i = 0;
	while(!glfwWindowShouldClose(window)) {
        space = updatePhysics(space);
        i--;
        if (i < 0) {
            space = controlPower(space);
            drawSpace(window, space);
            i = 100;
        }
        usleep(1);
	}
	glfwTerminate();
    close_keyboard();
    return 1;
}
