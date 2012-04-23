CC=gcc

uimake: src/Simple-UI.c
	gcc -o simple simple.c `pkg-config --libs --cflags gtk+-2.0`