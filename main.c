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

struct times {
	int value;
	struct times * next;
};

/******** FUNCTIONS ********/

// outputs list

void output_list(struct times * list){
	
	struct times * cur = list;
	if(list != 0){
		printf("test");
		while(cur->next != 0){
			printf("value: %d \n", cur->value);
			cur = cur->next;
		}
		printf("value: %d", cur->value);
	}else {
		printf("No Values");
	}
}


// get the burst times from the user

void add_burst_time(struct times * list, int new_time){
	
	printf("test");
	
	struct times * temp;
	struct times * cur;
	temp = (struct times *) malloc( sizeof(struct times) );	
	temp->value = new_time;
	temp->next = 0;	
	
	if(temp == 0){
		printf("Out of memory from adding to list");
		return;
	}else {

		if(list == 0){
			list = temp;
		}else {
printf("tst");
			while(cur->next != 0){
				cur = cur->next;
			}
			cur->next = temp;
			temp = list;
		}

	}
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
	int tempNum = 0;
	struct times * burstList = 0;
		
	printf("Welcome to the Job Scheduler Computer.\nWhat algorithm would you like to use\n");
	scanf("%s", algor);
	
	check = get_algorithm(algor);

	if(check){		
		// check if algorithm is round robin (RR)
		
		if(check == 4){
			while(timeRetrieve == 1){
				printf("What is the time quanta for %s scheduling\n", algor);
				scanf("%d", &tempNum);
 				if(tempNum > 0){
 					add_burst_time(burstList, tempNum);
 				}else {
 					printf("Input terminated\n");
 					timeRetrieve = 0;
 				}

			}
//			output_list(burstList);
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