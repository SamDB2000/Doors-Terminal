#Makefile for the doors game

doors: doors.c
	gcc -o doors.c doors

clean:
	rm doors
