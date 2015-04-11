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


struct times;
typedef struct times * burstNode;

struct times {
	int value;
	burstNode next;
};

/******** FUNCTIONS ********/

// outputs list

void output_list(burstNode list){
	
	burstNode cur = list;

	while(cur->next != NULL){
		printf("value: %d \n", cur->value);
		cur = cur->next;
	}
		printf("value: ", cur->value);
}


// get the burst times from the user

void add_burst_time(burstNode list, int new_time){
	
	burstNode temp;
	temp = (struct times *) malloc( sizeof(struct times) );
	temp->value = new_time;
	temp->next = NULL;
	
	burstNode cur = list;
	while(cur->next != NULL){
		cur = cur->next;
	}
	cur->next = temp;
	temp = list;
}


// convert the selected choice into a numeric identifier

// 1 - FCFS
// 2 - SJF
// 3 - SRT
// 4 - RR
// 0 - Invalid selection

int get_algorithm(const char * userSelect){
	
	if(strcmp(userSelect, "FCFS") == 0){
		return 1;
	}else if(strcmp(userSelect, "SJF") == 0){
		return 2;
	}else if(strcmp(userSelect, "SRT") == 0){
		return 3;
	}else if(strcmp(userSelect, "RR")== 0){
		return 4;
	}else {
		return 0;
	}
}

/**********************************************************************************************************************************
****************************************************** MAIN **********************************************************************
***********************************************************************************************************************************/

int main(){

	char algor[10];
	int quanta = 0;
	int check = 0;
	int timeRetrieve = 1;
	int * burstTimes = NULL;
		
	printf("Welcome to the Job Scheduler Computer.\nWhat algorithm would you like to use\n");
	scanf("%s", algor);
	
	check = get_algorithm(algor);
	if(check){
		
		// check if algorithm is round robin (RR)
		
		if(check == 4){
			printf("What is the time quanta for %s scheduling\n", algor);
			while(timeRetrieve == 1){
				
			
			}
			//get_burst_times();
		}else {
		
		}
	}else {
		printf("You didn't enter a valid algorithm. Process terminated!\n");		
	}

	
	return 0;
}

/**********************************************************************************************************************************
***********************************************************************************************************************************
***********************************************************************************************************************************/