#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "headers/space.h"

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

void controlPower(struct Space* space) {
    if (kbhit() == 1) {
        switch (readch()) {
            case 'f':
                space->ship->ax = 1;
                printf("right\n");
                break;
            case 's':
                space->ship->ax = -1;
                printf("left\n");
                break;
            case 'e':
                space->ship->ay = 1;
                printf("up\n");
                break;
            case 'd':
                space->ship->ay = -1;
                printf("down\n");
                break;
        }
        fflush(stdout);
    } else {
        space->ship->ax = 0;
        space->ship->ay = 0;
    }
}
