#!/bin/sh

gcc -g3  -o Philo sdl.c `sdl-config --cflags --libs`  -lSDLmain -lSDL -lSDL_image