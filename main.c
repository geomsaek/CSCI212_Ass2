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

// get the wait time
void get_wait_time(struct times ** list){

	printf("\n");
	printf("Computing Wait times\n\n");
	printf("\n");
	
	struct times * temp;
	temp = *list;
	int processCounter = 1;
	int startTime = 0;
	
	if(temp == 0){
		printf("Nothing in the list\n");
	}else {
		while(temp->next != 0){
			if(startTime == 0){
				printf("P%d\t\t%d\n", processCounter, startTime);
				startTime = temp->value;
			}else {
				printf("P%d\t\t%d\n", processCounter, startTime);
				startTime = startTime + temp->value;
			}
			temp = temp->next;
			processCounter++;
		}
		printf("P%d\t\t%d\n", processCounter, startTime);
	}
}

// get average turn around time

void get_turn_around(struct times ** list){

	printf("\n");
	printf("Computing Turn around times\n\n");
	printf("\n");
	
	struct times * temp;
	temp = *list;
	int processCounter = 1;
	int startTime = 0;
	
	if(temp == 0){
		printf("Nothing in the list\n");
	}else {
		while(temp->next != 0){
			startTime = startTime + temp->value;
			printf("P%d\t\t%d\n", processCounter, startTime);
			temp = temp->next;
			processCounter++;
		}
		printf("P%d\t\t%d\n", processCounter, startTime);
	}
	
}

// outputs the values based on the Round Robin values (RR)

void rr_algorithm(struct times ** list){
	
	printf("\n");
	printf("Scheduled Jobs\n\n");
	printf("Process\t\t\tBurst Time\t\t\tStart Time\t\t\tStop Time\n");
	
	struct times * temp;
	temp = *list;
	int processCounter = 1;
	
	if(temp == 0){
		printf("Nothing in the list\n");
	}else {
		while(temp->next != 0){
			printf("P%d\t\t\t%d\t\t\t0\t\t\t%d\n", processCounter, temp->value, temp->value);
			temp = temp->next;
			processCounter++;
		}
		printf("%d\n", temp->value);
	}
		
	printf("\n");
}

// outputs the values based on the FCFS algorithm

void fcfs_algorithm(struct times ** list){

	printf("\n");
	printf("************* FIRST COME FIRST SERVED (FCFS) *************\n\n");
	printf("Scheduled Jobs\n\n");
	printf("Process\t\t\tBurst Time\t\t\tStart Time\t\t\tStop Time\n");

	struct times * temp;
	temp = *list;
	int processCounter = 1;
	int startTime = 0;
	int stopTime = 0;
	
	if(temp == 0){
		printf("Nothing in the list\n");
	}else {
		while(temp->next != 0){
			if(startTime == 0){
				printf("P%d\t\t\t%d\t\t\t\t\%d\t\t\t\t%d\n", processCounter, temp->value, startTime, stopTime);
				stopTime = temp->value;
				startTime = temp->value;
			}else {
				stopTime = stopTime + temp->value;
				printf("P%d\t\t\t%d\t\t\t\t\%d\t\t\t\t%d\n", processCounter, temp->value, startTime, stopTime);
				startTime = stopTime;
			}
			temp = temp->next;
			processCounter++;
		}
		stopTime = stopTime + temp->value;
		printf("P%d\t\t\t%d\t\t\t\t\%d\t\t\t\t%d\n", processCounter, temp->value, startTime, stopTime);
	}
	get_wait_time(list);
	get_turn_around(list);
	printf("\n");
}

// outputs the values based on the SJF algorithm

void sjf_algorithm(struct times ** list){

	printf("\n");
	printf("************* SHORTEST JOB FIRST (SJF) *************\n\n");
	printf("Scheduled Jobs\n\n");
	printf("Process\t\t\tBurst Time\t\t\tStart Time\t\t\tStop Time\n");

	struct times * temp;
	temp = *list;
	int processCounter = 1;
	int startTime = 0;
	int stopTime = 0;
	
	if(temp == 0){
		
		
	}else {
		
	}
	

	
	printf("\n");
}

//outputs the values based on the SRT algorithm
void srt_algorithm(struct times ** list){
	printf("\n");
	printf("Scheduled Jobs\n\n");
	printf("Process\t\t\tBurst Time\t\t\tStart Time\t\t\tStop Time\n");
	
	
	
	printf("\n");
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

// 1 - FCFS
// 2 - SJF
// 3 - SRT
// 4 - RR

// select the correct algorithm
void output_algorithm(struct times ** list, int choice){
	
	switch(choice){
	
		case 1:
			// FCFS
			fcfs_algorithm(list);
		break;

		case 2:
			// SJF
			sjf_algorithm(list);
		break;
		
		case 3:
			// SRT 
			srt_algorithm(list);
		break;
		
		case 4:
			// RR
			rr_algorithm(list);
		break;
 	}

}


/**********************************************************************************************************************************
****************************************************** MAIN **********************************************************************
***********************************************************************************************************************************/

int main(){

	char algor[10];
	// value for quanta - RR only
	int quanta = 0;
	int check = 0;
	int timeRetrieve = 1;
	int tempNum = 0;
	int processCount = 1;
	struct times * burstList = 0;

	printf("Welcome to the Job Scheduler Computer.\nWhat algorithm would you like to use\n");
	scanf("%s", algor);
	
	check = get_algorithm(algor);

	if(check){		
		// check if algorithm is round robin (RR)
		if(check == 4){		
			printf("What is the time quanta for %s scheduling\n", algor);
			scanf("%d", &quanta);
		}
		
		while(timeRetrieve == 1){
			printf("Process %d (P%d) – What is the burst time?\n",processCount, processCount);
			
			scanf("%d", &tempNum);
			if (!feof(stdin)){
				add_burst_time(&burstList, tempNum);
			}else {
				printf("Input terminated\n");
				timeRetrieve = 0;
			}
			processCount++;
		}
		
		output_algorithm(&burstList, check);

// output the list to check values exist
//		output_list(&burstList);

	}else {
		printf("You didn't enter a valid algorithm. Process terminated!\n");		
	}
	
	return 0;
}

/**********************************************************************************************************************************
***********************************************************************************************************************************
***********************************************************************************************************************************/