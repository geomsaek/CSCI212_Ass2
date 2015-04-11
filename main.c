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

// outputs the values based on the Round Robin values (RR)

void round_robin(struct times ** list){
	
	


}



// outputs list - more of a sanity check to ensure list values are present
void output_list(struct times ** list){
	
	struct times * temp;
	temp = *list;
	
	if(temp == 0){
		printf("Nothing in the list\n");
	}else {
		while(temp->next != 0){
			printf("%d\n", temp->value);
			temp = temp->next;
		}
		printf("%d\n", temp->value);
	}
	
}

// get the burst times from the user

void add_burst_time(struct times ** list, int new_time){
	
	struct times * temp, *r;
	temp = * list;
	
	if(temp == 0){
		temp = ((struct times *) malloc(sizeof(struct times)));
		temp->value = new_time;
		temp->next = 0;
		*list = temp;
	}else {
		while(temp->next != 0){
			temp = temp->next;
		}
		r = ((struct times *)malloc(sizeof(struct times)));
		r->value = new_time;
		r->next = 0;
		temp->next = r;
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
	char endof;
	int c;
		
	printf("Welcome to the Job Scheduler Computer.\nWhat algorithm would you like to use\n");
	scanf("%s", algor);
	
	check = get_algorithm(algor);

	if(check){		
		// check if algorithm is round robin (RR)
		if(check == 4){
			while(timeRetrieve == 1){
				printf("What is the time quanta for %s scheduling\n", algor);
				scanf("%d", &tempNum);				
				if (!feof(stdin)){
 					add_burst_time(&burstList, tempNum);
 				}else {
 					printf("Input terminated\n");
 					timeRetrieve = 0;
 				}
			}
			output_list(&burstList);
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