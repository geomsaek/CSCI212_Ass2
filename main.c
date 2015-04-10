/**
*
*	Name:		Matthew Saliba
*	Desc:		CSCI212 - Ass 2: Task 1
*	S #:		3284165
*	Sub:		CSCI212
*	Mod:		
*
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/******** FUNCTIONS ********/

int get_algorithm(const char * userSelect, const char * algorithm){
	int re = 0;
	
	re = strcmp(userSelect, algorithm);
	
	if(re == 0){
		return 1;
	}else {
		return 0;
	}
}


/***************************/

int main(){

	char algor[10];
	int quanta = 0;
	int check = 0;
		
	printf("Welcome to the Job Scheduler Computer.\n What algorithm would you like to use\n");
	scanf("%s", algor);
	
	printf("What is the time quanta for %s scheduling\n", algor);
	scanf("%i", &check);
	
	return 0;
}
