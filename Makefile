#	NAME: Matt Saliba
#	S#:	  3284165
#	Assignment 2 Makefile
#	PURPOSE: This make file compiles the program c files for task1

all:	sched1 sched2

sched1:	 sched1.o
		  gcc sched1.o -o sched1	

sched1.o: sched1.c
		 gcc	-c sched1.c
		 
sched2:	 sched2.o
		  gcc sched2.o -o sched2	

sched2.o: sched2.c
		 gcc	-c sched2.c