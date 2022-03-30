For Mac users
```
gcc graphic.c physics.c space.c main.c -o main -lglfw -framework OPENGL -framework GLUT -lGLEW -lncurses; ./main
```
For Linux users (tested on Ubuntu 20.04.4)
```
gcc graphic.c physics.c space.c main.c -o main -lglfw -lGL -lglut -lGLEW -lncurses -lm; ./main
```
