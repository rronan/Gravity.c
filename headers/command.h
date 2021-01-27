#ifndef COMMAND_H
# define COMMAND_H

struct Space;

void init_keyboard();

void close_keyboard();

int kbhit();

int readch();

void controlPower(struct Space*);

#endif


