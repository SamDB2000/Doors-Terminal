#Makefile for the doors game

doors: doors.o
	gcc -o doors doors.o

doors.o: doors.c
	gcc -c doors.c

clean:
	rm *.o
