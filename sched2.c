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
	int searched;
	struct times * next;
};

struct summary {
	int pid;
	int time;
	struct summary * next;
};

/***********************************************************************************************************************************
******************************************************** HELPER FUNCTIONS *****************************************************************
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
		temp->searched = 0;
		temp->next = 0;
		*list = temp;
	}else {
		while(temp->next != 0){
			temp = temp->next;
		}
		r = ((struct times *)malloc(sizeof(struct times)));
		r->burst = new_burst;
		r->arrival = new_arrival;
		r->searched = 0;
		r->next = 0;
		temp->next = r;
	}
	
}

// marks the shortest number with a minus -1;
void reset_searched_markers(struct times ** list){
	
	struct times * temp;
	temp = *list;
	
	while(temp->next != 0){
		temp->searched = 0;
		temp = temp->next;
	}
	temp->searched = 0;	
	
}

// marks the shortest number with a minus -1;
void mark_shortest(struct times ** list, int index){
	
	struct times * temp;
	temp = *list;
	int counter = 0;
	
	while(temp->next != 0){
		if(counter == index){
			temp->searched = -1;
		}
		counter = counter + 1;
		temp = temp->next;
	}
	if(counter == index){
		temp->searched = -1;
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
			
			if(temp->searched != -1){
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
		if(temp->searched != -1){
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

int check_shorter_time(struct times ** list, int curArrive){

	struct times * cur;
	cur = *list;
	int shorter = 0;
	
	while(cur->next != 0){
		if(cur->arrival < curArrive){
			if(cur->searched != -1){
				shorter = 1;
				cur->searched = -1;
			}
		}
		cur = cur->next;
	}
	if(shorter == 0){
		if(cur->arrival < curArrive){
			if(cur->searched != -1){
				shorter = 1;
				cur->searched = -1;
			}
		}		
	}
	
	return shorter;
}

// returns an integer relating to the length of a list
int get_list_length(struct times ** list){
	
	struct times * cur;
	cur = *list;
	int count = 0;
	
	
	if(list == 0){
		return 0;
	}else {
		while(cur->next != 0){
			cur = cur->next;
			count = count + 1;
		}
		count = count + 1;
		return count;
	}
	
}

// sorts a list into descending order
void listsort(struct times ** list){
	
	struct times * tmpPtr = *list;
	struct times * tmpNxt = tmpPtr->next;
	int tmpArrive = 0;
	int tmpBurst = 0;
	
	if(list != 0){
	
		while(tmpNxt != NULL){
		   while(tmpNxt != tmpPtr){
					if(tmpNxt->arrival < tmpPtr->arrival){
						tmpArrive = tmpPtr->arrival;
						tmpBurst = tmpPtr->burst;
						
						tmpPtr->arrival = tmpNxt->arrival;
						tmpPtr->burst = tmpNxt->burst;
						tmpPtr->searched = 0;
						tmpNxt->arrival = tmpArrive;
						tmpNxt->burst = tmpBurst;
					}
					tmpPtr = tmpPtr->next;
			}
			tmpPtr = *list;
			tmpNxt = tmpNxt->next;
		}
	}

}

/***********************************************************************************************************************************
******************************************************** SUMMARIES ****************************************************************
***********************************************************************************************************************************/

// computing wait times for fcfs algorithm
void fcfs_wait_time(struct times ** list){
	
	printf("\n");
	printf("Computing Wait times\n");
	printf("\n");
	
	struct times * temp;
	temp = *list;
	int startTime = 0, processing = 1, processCounter = 1, first = 0, stopTime = 0;

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
					startTime = stopTime - *lowArrive;
					stopTime = startTime + *lowBurst;
				}
				printf("P%d\t%d\n",processCounter, startTime);
				
			}else {
				processing = 0;
			}
			processCounter++;
		}
	}
	
}

// computing turn around times for fcfs algorithm
void fcfs_turn_around(struct times ** list){

	printf("\n");
	printf("Computing Turn around times\n");
	printf("\n");
	
	struct times * temp;
	temp = *list;
	int turnaround = 0, processing = 1, processCounter = 1, first = 0;

	int * lowArrive;
	int * lowBurst;
	
	if(temp == 0){
		printf("Nothing in the list\n");
	}else {

		while(processing == 1){

			findshortest(&temp, &lowBurst, &lowArrive);
			
			if(*lowArrive != -1){
				if(first == 1){
					turnaround = *lowBurst - *lowArrive;
				}else {
					turnaround = turnaround + (*lowBurst - *lowArrive);

				}

				printf("P%d\t%d\n",processCounter, turnaround);
				
			}else {
				processing = 0;
			}
			processCounter++;
		}
	}
}


/***********************************************************************************************************************************
******************************************************** ALGORITHMS ****************************************************************
***********************************************************************************************************************************/

// outputs the values based on the FCFS algorithm

void fcfs_algorithm(struct times ** list){

	struct times * temp;
	temp = *list;
	int processCounter = 1, startTime = 0, stopTime = 0, first = 1, processing = 1;
	
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
		reset_searched_markers(list);
		fcfs_wait_time(list);
		reset_searched_markers(list);
		fcfs_turn_around(list);
	}
}


int find_index(struct times ** list, int curIndex){

	struct times * cur = *list;	
	int nextIndex = curIndex + 1;
	int nextArrive = 0;
	int counter = 0;
	
	while(cur->next != 0){
	
		if(counter == nextIndex){
			nextArrive = cur->arrival;
		}
		cur = cur->next;
		counter = counter + 1;
	}
	return nextArrive;

}

//outputs the values based on the SJF algorithm

int get_next(struct times ** list, int curIndex, int arrive_burst){

	struct times * cur = *list;
	int counter = 0;
	int nextVal = 0;
	int found = 0;
	
	while(cur->next != 0){
		
		if(counter == curIndex + 1){
			if(arrive_burst == 1){
				nextVal= cur->burst;
			}else {
				nextVal= cur->arrival;
			}
			found = 1;
		}
		cur = cur->next;
		counter = counter + 1;
	}
	if(counter == curIndex + 1){
		if(arrive_burst == 1){
			nextVal= cur->burst;
		}else {
			nextVal = cur->arrival;
		}
		found = 1;
	}
	
	if(found == 1){
		return nextVal;
	}else {
		return -1;
	}
	
}

void switch_location(struct times ** list, struct times ** cur, int counter){
	
	struct times * temp = *list;
	int incre = 0;
	
	while(temp->next != 0){
		
		
		temp = temp->next;
	}
	
}

int find_next_lowest(struct times ** list, struct times * locate){

	int lowest = 999;
	struct times * cur = *list;
	int find = 0;
	
	while(cur->next != 0){
		if(cur->burst != -1){
			if(lowest > cur->burst){
				locate = cur;
				find = 1;
			}
		}
		cur = cur->next;
	}
	if(cur->burst != -1){
		if(lowest > cur->burst){
			locate = cur;
			find = 1;
		}	
	}
	if(find == 0){
		return -1;
	}else {
		return 1;
	}
	
}

void sjf_algorithm(struct times ** list){
	
	struct times * cur = *list;
	struct times * ahead = *list;
	ahead = ahead->next;
	int counter = 0;
	
	printf("\n");	
	
	if(list != 0){

		listsort(list);		
		output_list(list);	

		burstCounter = cur->burst;
		curArrive = cur->arrival;
		nextArrive = get_next(list, counter, 0);
		nextBurst = get_next(list, counter, 1);
		arrivalPointer = 0;
		
//		while(processing == 1){
		while(counter < 10){
			

			
			counter = counter + 1;
			
		}
		printf("\n");
	}else {
		printf("Nothing in the list\n");
	}
	
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
			sjf_algorithm(list);
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
	
	add_processes(&burstList, 8, 0);
	add_processes(&burstList, 6, 1);
	add_processes(&burstList, 6, 2);
	add_processes(&burstList, 2, 3);
	add_processes(&burstList, 3, 4);
	add_processes(&burstList, 1, 5);
	output_algorithm(&burstList, 2,0);

/*
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
	}*/
	
	return 0;
}

/**********************************************************************************************************************************
***********************************************************************************************************************************
***********************************************************************************************************************************/