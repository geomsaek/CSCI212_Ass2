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
	int burst;
	int arrival;
	struct times * next;
};

struct summary {
	int pid;
	int time;
	struct summary * next;
};

/***********************************************************************************************************************************
******************************************************** FUNCTIONS *****************************************************************
***********************************************************************************************************************************/

// outputs list - more of a sanity check to ensure list values are present
void output_list(struct times ** list){
	
	struct times * temp;
	temp = *list;
	
	if(temp == 0){
		printf("Nothing in the list\n");
	}else {
		while(temp->next != 0){
			printf("Burst: %d -- Arrival: %d\n", temp->burst, temp->arrival);
			temp = temp->next;
		}
		printf("Burst: %d -- Arrival: %d\n", temp->burst, temp->arrival);
	}
	
}

// add values to list pointer - struct: times
void add_processes(struct times ** list, int new_burst, int new_arrival){
	
	struct times * temp, *r;
	temp = * list;
	
	if(temp == 0){
		temp = ((struct times *) malloc(sizeof(struct times)));
		temp->burst = new_burst;
		temp->arrival = new_arrival;

		temp->next = 0;
		*list = temp;
	}else {
		while(temp->next != 0){
			temp = temp->next;
		}
		r = ((struct times *)malloc(sizeof(struct times)));
		r->burst = new_burst;
		r->arrival = new_arrival;
		r->next = 0;
		temp->next = r;
	}
	
}


// marks the shortest number with a minus -1;
void mark_shortest(struct times ** list, int index){
	
	struct times * temp;
	temp = *list;
	int counter = 0;
	
	while(temp->next != 0){
		if(counter == index){
			temp->arrival = -1;
			temp->burst = -1;
		}
		counter = counter + 1;
		temp = temp->next;
	}
	if(counter == index){
		temp->arrival = -1;
		temp->burst = -1;
	}
	
}

// finds the shortest number and marks the number with a -1
void findshortest(struct times ** list, int ** low_burst, int ** low_arrival){

	struct times * temp;
	temp = *list;
	int shortArrive = 9999;
	int shortBurst = 0;
	int shortLocate = 0;
	int counter = 0;
	int found = 0;
	int marker = -1;
	
	
	int * tempBurst = *low_burst;
	//int * tempArrive = *low_arrival;
	
	
	if(temp != 0){

		while(temp->next != 0){
			
			if(temp->arrival != -1){
				if(temp->arrival < shortArrive){
					shortArrive = temp->arrival;
					shortBurst = temp->burst;
					*low_burst = &shortBurst;
					*low_arrival = &shortArrive;

					shortLocate = counter;
					found = 1;
				}
			}
			counter = counter + 1;
			temp = temp->next;
		}
		if(temp->arrival != -1){
			if(temp->arrival < shortArrive){
				shortArrive = temp->arrival;
				shortBurst = temp->burst;
				*low_burst = &shortBurst;
				*low_arrival = &shortArrive;
				shortLocate = counter;
				found = 1;
			}
		}
		if(found == 0){
			*low_arrival = &marker;
		}
		mark_shortest(list, shortLocate);
	}else {
		return;
	}

}

/***********************************************************************************************************************************
******************************************************** SUMMARIES ****************************************************************
***********************************************************************************************************************************/

void fcfs_wait_time(struct times ** list){
	printf("\n");
	printf("Computing Wait times\n\n");
	printf("\n");
	
	struct times * temp;
	temp = *list;
	int processCounter = 1;
	int startTime = 0, processing = 1, processCounter = 0;

	int * lowArrive;
	int * lowBurst;
	
	if(temp != 0){
		while(processing == 1){
			findshortest(&temp, &lowBurst, &lowArrive);
			
			if(*lowArrive != -1){
				
			}else {
				processing = 0;
			}
			processCounter++;
		}
		
	}else {
		return;
	}
	
}


/***********************************************************************************************************************************
******************************************************** ALGORITHMS ****************************************************************
***********************************************************************************************************************************/

// outputs the values based on the FCFS algorithm

void fcfs_algorithm(struct times ** list){

	struct times * temp;
	temp = *list;
	int processCounter = 1;
	int startTime = 0;
	int stopTime = 0;
	int first = 1;
	
	int processing = 1;
	
	int * lowArrive;
	int * lowBurst;
	
	
	if(temp == 0){
		printf("Nothing in the list\n");
	}else {
	
		while(processing == 1){
		
			findshortest(&temp, &lowBurst, &lowArrive);
			
			if(*lowArrive != -1){
				if(first == 1){
					startTime = *lowArrive;
					stopTime = startTime + *lowBurst;
					first = 0;
				}else {
					startTime = stopTime;
					stopTime = stopTime + *lowBurst;
				}
				printf("P%d\t\t\t%d\t\t\t\t\%d\t\t\t\t%d\n", processCounter, *lowBurst, startTime, stopTime);
				startTime = *lowArrive;

			}else {
				processing = 0;
			}
			processCounter++;

			
		}
	}
	fcfs_wait_time(list);
	fcfs_turn_around(list);
	printf("\n");
}

/***********************************************************************************************************************************
******************************************************** FUNCTIONS *****************************************************************
***********************************************************************************************************************************/

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
void output_algorithm(struct times ** list, int choice, int quanta){
	
	switch(choice){
	
		case 1:
			// FCFS
			printf("\n");
			printf("************* FIRST COME FIRST SERVED (FCFS) *************\n\n");
			printf("Scheduled Jobs\n\n");
			printf("Process\t\t\tBurst Time\t\t\tStart Time\t\t\tStop Time\n");
			fcfs_algorithm(list);
		break;

		case 2:
			// SJF
			printf("\n");
			printf("************* SHORTEST JOB FIRST (SJF) *************\n\n");
			printf("Scheduled Jobs\n\n");
			printf("Process\t\t\tBurst Time\t\t\tStart Time\t\t\tStop Time\n");
//			sjf_algorithm(list);
		break;
		
		case 3:
			// SRT 
			printf("\n");
			printf("************* SHORTEST RETURN TIME FIRST (SRT) *************\n\n");
			printf("Scheduled Jobs\n\n");
			printf("Process\t\t\tBurst Time\t\t\tStart Time\t\t\tStop Time\n");
//			srt_algorithm(list);
		break;
		
		case 4:
			// RR
			printf("\n");
			printf("************* ROUND ROBIN (R) *************\n\n");
			printf("Quanta Time: %d\n", quanta);
			printf("Scheduled Jobs\n\n");
			printf("Process\t\t\tBurst Time\t\t\tStart Time\t\t\tStop Time\n");
//			rr_algorithm(list, quanta);
		break;
 	}

}

/**********************************************************************************************************************************
****************************************************** MAIN **********************************************************************
***********************************************************************************************************************************/

int main(){

	char algor[10];
	// value for quanta - RR only
	int quanta = 0, check = 0, timeRetrieve = 1, processCount = 1, tempNum = 0, tempProcess = 0;
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
			printf("Process %d (P%d) – What is the burst time & start time?\n",processCount, processCount);
			scanf("%d%d", &tempNum, &tempProcess);
			if (!feof(stdin)){
				add_processes(&burstList, tempNum, tempProcess);
			}else {
				printf("Input terminated\n");
				timeRetrieve = 0;
			}
			processCount++;
		}
//		output_list(&burstList);
		output_algorithm(&burstList, check, quanta);

	}else {
		printf("You didn't enter a valid algorithm. Process terminated!\n");		
	}
	
	return 0;
}

/**********************************************************************************************************************************
***********************************************************************************************************************************
***********************************************************************************************************************************/