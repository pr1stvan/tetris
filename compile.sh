#!/bin/bash

gcc *.c -o tetris $(sdl-config --cflags --libs) -lSDL_ttf -lSDL_gfx
