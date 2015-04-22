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

// marks the shortest number with a minus -1;
void sjf_mark_shortest(struct times ** list, int index){
	
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


int sjf_findshortest(struct times ** list){

	struct times * temp;
	temp = *list;
	int shortest = 9999;
	int shortLocate = 0;
	int counter = 0;
	int found = 0;
	
	while(temp->next != 0){
			
		if(temp->searched != -1){
			if(temp->burst < shortest){
				shortest = temp->burst;
				shortLocate = counter;
				found = 1;
			}
		}
		counter = counter + 1;
		temp = temp->next;
	}
	if(temp->searched != -1){
		if(temp->burst < shortest){
			shortest = temp->burst;
			shortLocate = counter;
			found = 1;
		}
	}
	sjf_mark_shortest(list, shortLocate);	

	if(found > 0){

		return shortest;
	}else {
		return -1;
	}
}


void add_burst_time(struct times ** list, int new_time){
	
	struct times * temp, *r;
	temp = * list;
	
	if(temp == 0){
		temp = ((struct times *) malloc(sizeof(struct times)));
		temp->burst = new_time;
		temp->next = 0;
		*list = temp;
	}else {
		while(temp->next != 0){
			temp = temp->next;
		}
		r = ((struct times *)malloc(sizeof(struct times)));
		r->burst = new_time;
		r->next = 0;
		temp->next = r;
	}
	
}

void sjf_remainder(struct times ** list){

	int processCounter = 1, startTime = 0, stopTime = 0, searching = 1, curShort = 0, counter = 0;	
	struct times * visited = 0;
	struct times * temp;
	struct times * wait = 0;
	struct times * turnaround = 0;
	printf("************* SHORTEST JOB FIRST (SJF) *************\n\n");
			printf("Scheduled Jobs\n\n");
			printf("Process\t\t\tBurst Time\t\t\tStart Time\t\t\tStop Time\n");
	temp = *list;
	if(temp == 0){
		return;
	}else {
		while(searching == 1){
			
			curShort = sjf_findshortest(list);
			if(curShort == -1){
				searching = 0;
			}else {
				stopTime = startTime + curShort;
				add_burst_time(&wait, startTime);
				add_burst_time(&turnaround, stopTime);
				printf("P%d\t\t\t%d\t\t\t\t\%d\t\t\t\t%d\n", counter, curShort, startTime, stopTime);
				startTime = startTime + curShort;
			}
			
			counter++;
		}
	}
	
}

void sjf_algorithm(struct times ** list){
	
	struct times * cur = *list;
	struct times * ahead = *list;
	
	struct times * wait = 0;
	struct times * turnaround = 0;
	
	int processing = 1, allArrive = 0, counter = 0, executeCycle = 0, setBurst = 1;
	
	
	
	int curBurst = 0, curArrive = 0;
	int lastCycle = 0;
	
	if(list != 0){
		// set the next pointer
		ahead = ahead->next;
		listsort(list);
		//output_list(list);
		
		while(processing == 1){
			if(allArrive == 1){
				cur = *list;
				output_list(list);
				sjf_remainder(list);
				printf("All arrive\n");
				processing = 0;
			}else {
				
				if(lastCycle == 1){

					while(cur->burst > 0){
						printf("LAST BURST: %d, LAST ARRIVE: %d\n:", cur->burst, cur->arrival);						
						cur->burst = cur->burst -1;
					}
					cur->searched = -1;
					allArrive = 1;
				}else {
					curArrive = ahead->arrival;
					while(executeCycle < 1){
						printf("Statement 1: ");
						printf("BURST DECRE: BEFORE: %d:", cur->burst);
						cur->burst = cur->burst -1;
						printf("BURST DECRE: AFTER: %d:\n\n", cur->burst);
						executeCycle++;
					}
					counter = counter + 1;
					printf("COUNTER: %d" , counter);
					if(counter == curArrive){
						printf("Statement 2: ");
						printf("///OK NEW ARRIVAL HAS COME IN//");
						printf("ARRIAL: %d, BURST: %d", ahead->arrival, ahead->burst);
					
						if(ahead->burst < cur->burst){
							printf("Statement 3: ");
							printf("--SWITCH--");
							cur = ahead;
							executeCycle = 0;
						}else {
							printf("Statement 4: ");
							printf("--CONTINUE--");
							if(cur->burst >0){
								printf("Statement 5: ");
								printf("((((cycle is ongoing)))");
								executeCycle = 0;
							}else {
								printf("Statement 6: ");
								if(cur->next != 0){
									printf("Statement 7: ");
									// this might need to be checked
									printf("((((cycle has ended moving to next)))");
									cur->searched = -1;
									cur = ahead;
								}else {
									printf("Statement 7: ");
									printf("((((cycle has ended and list has ended)))");
									cur->searched = -1;
									lastCycle = 1;
								}
							}
						}
					
					}else {
						printf("Statement 8: ");
						printf("--counter not equal to ahead arrive--");
					
						if(cur->burst > 0){
							printf("Statement 9: ");
							executeCycle = 0;
						}else {
							printf("Statement 10: ");
							if(cur->next != 0){
								printf("Statement 11: ");
								// this might need to be checked
								printf("((((cycle has ended moving to next)))");
								cur->searched = -1;
								cur = ahead;
							}else {
								printf("Statement 12: ");
								printf("((((cycle has ended and list has ended)))");
								cur->searched = -1;
								lastCycle = 1;
							}
						}
					}
					if(ahead->next != 0){
						printf("Statement 13: ");
						ahead = ahead->next;
						printf("&&& NEXT BURST &&& %d, ARRIVAL: %d", ahead->burst, ahead->arrival);
					}
				
					printf("\n");
					printf("\n");
				}
			}
			
		}

		
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