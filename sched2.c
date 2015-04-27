/**
*
*	Name:		Matthew Saliba
*	Desc:		CSCI212 - Ass 2: Task 2
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
	int index;
	int searched;
	struct times * next;
};

struct summary {
	int pid;
	int time;
	struct summary * next;
};

/***********************************************************************************************************************************
******************************************************** HELPER FUNCTIONS - SRT ALGORITHM ******************************************
***********************************************************************************************************************************/

// marks the shortest number with a minus -1;
void srt_mark_shortest(struct times ** list, int index){
	
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

int srt_findshortest(struct times ** list){

	struct times * temp;
	temp = *list;
	int shortest = 9999;
	int counter = 0;
	int shortLocate = 0;
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
			shortLocate = counter;
			shortest = temp->burst;
			found = 1;
		}
	}
	srt_mark_shortest(list, shortLocate);
	if(found > 0){
		return shortest;
	}else {
		return -1;
	}
}

// repeated function to track index, had issues with this so had to use something that worked at the time
int srt_find_index(struct times ** list){

	struct times * temp;
	temp = *list;
	int shortest = 9999, counter = 0, shortLocate = 0,  found = 0;
	
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
			shortLocate = counter;
			shortest = temp->burst;
			found = 1;
		}
	}

	if(found > 0){
		return shortLocate;
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

int get_last_val(struct times ** list){

	struct times * cur;
	cur = * list;
	int last = 0;
	
	while(cur->next != 0){
		cur = cur->next;
	}
	last = cur->burst;
	last = last + 1;
	return last;
	
}

void output_srt_summary(struct times ** curWait, struct times ** plist, char message[50]){

	struct times * curProcess = *plist;
	struct times * waits = *curWait;
	
	printf("\n");
	printf("%s", message);
	printf("\n");
	while(waits->next != 0){
		printf("P%d\t\t\t%d\n", curProcess->burst, waits->burst);
		curProcess = curProcess->next;
		waits = waits->next;
	}
	printf("P%d\t\t\t%d\n", curProcess->burst, waits->burst);
	printf("\n");
}


void srt_remainder(struct times ** list, struct times ** wait, struct times ** turnaround, struct times ** plist){

	int processCounter = 1, startTime = 0, stopTime = 0, searching = 1, curShort = 0, counter = 0;	
	struct times * visited = 0;
	struct times * temp;
	struct times * curWait = *wait;
	struct times * curTurn = *turnaround;
	int locate = 0;
	
	struct times * pNewList = *plist;
	
	startTime = get_last_val(&curWait);
	stopTime = get_last_val(&curWait);
	
	temp = *list;
	if(temp == 0){
		return;
	}else {
		while(searching == 1){
			
			locate = srt_find_index(list);
			curShort = srt_findshortest(list);
			if(curShort == -1){
				searching = 0;
			}else {
				stopTime = startTime + curShort;
				add_burst_time(&pNewList, locate);
				add_burst_time(&curWait, startTime);
				printf("P%d\t\t\t%d\t\t\t\t\%d\t\t\t\t%d\n", locate, curShort, startTime, stopTime);
				locate = 0;
				add_burst_time(&curTurn, stopTime);
				startTime = startTime + curShort;
			}
			
			counter++;
		}
	}
	
	char message[50] = { "Computing Wait Times\0" };
	output_srt_summary(&curWait, &pNewList, message);
	char turnMessage[50] = { "Computing Turn around Times\0" };
	output_srt_summary(&curTurn, &pNewList, turnMessage);
}

/***********************************************************************************************************************************
******************************************************** HELPER FUNCTIONS - SJF ALGORITHM ******************************************
***********************************************************************************************************************************/

int find_shortest_burst(struct times ** list, int time){

	struct times * cur = *list;
	int search = 0;
	int shortest = 99999;
	int foundIndex = -1;
	int counter = 0;

	while(cur->next != 0){
		if(cur->searched != -1){

			if(cur->arrival <= time){		
				if(cur->burst < shortest){
					shortest = cur->burst;
					foundIndex = counter;
				}
			}
		}

		cur = cur->next;
		counter = counter + 1;
	}
	
	if(cur->searched != -1){
		if(cur->arrival <= time){		
			if(cur->burst < shortest){
				shortest = cur->burst;
				foundIndex = counter;
			}
		}
	}

	return foundIndex;
}

struct times * get_shortest(struct times ** list, int time){
	
	struct times * cur = *list;
	int shortIndex = 0, counter =0, found = 0;

	shortIndex = find_shortest_burst(list, time);
	
	if(shortIndex != -1){
	
		while(cur->next != 0){
			if(counter == shortIndex){
				cur->searched = -1;
				return cur;
			}
			cur=cur->next;
			counter++;
		}
		if(counter == shortIndex){
			cur->searched = -1;
			return cur;
		}else {
			return *list;
		}
	
	}else {
		return *list;
	}
}

int find_by_index(struct times ** list, int index, int findArrival){

	struct times * cur = *list;
	int counter = 0;
	
	while(cur->next != 0){
		if(counter == index){
			if(findArrival){
				return cur->arrival;
			}else {
				return cur->burst;
			}
		}
		cur = cur->next;
		counter++;
	}
	if(counter == index){
		if(findArrival){
			return cur->arrival;
		}else {
			return cur->burst;
		}
	}else {
		return -1;
	}
}


/***********************************************************************************************************************************
******************************************************** HELPER FUNCTIONS **********************************************************
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

void index_list(struct times ** list){

	int counter = 1;
	struct times * cur = *list;
	
	while(cur->next != 0){
		cur->index = counter;
		cur = cur->next;
		counter = counter + 1;
	}
	cur->index = counter;

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
	index_list(list);

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


// preemptive version of the SJF algorithm
void srt_algorithm(struct times ** list){
	
	struct times * cur = *list;
	struct times * ahead = *list;
	struct times * plist = 0;
	struct times * wait = 0;
	struct times * turnaround = 0;
	
	int processing = 1, allArrive = 0, counter = 0, executeCycle = 0, setBurst = 1, curArrive = 0, lastCycle = 0, startTime = 0, stopTime = 0, processCounter = 1;

	if(list != 0){
		// set the next pointer
		ahead = ahead->next;
		listsort(list);
		
		while(processing == 1){
			if(allArrive == 1){
				cur = *list;
				srt_remainder(list, &wait, &turnaround, &plist);
				processing = 0;
			}else {				
				if(lastCycle == 1){
					while(cur->burst > 0){
						cur->burst = cur->burst -1;
						stopTime = stopTime+1;
					}
					startTime = startTime + cur->burst;
					cur->searched = -1;
					allArrive = 1;
				}else {
					curArrive = ahead->arrival;
					add_burst_time(&wait, stopTime);
					printf("P%d\t\t\t%d\t\t\t\t%d", cur->index, cur->burst, stopTime);
					add_burst_time(&plist, cur->index);
					while(executeCycle < 1){
						cur->burst = cur->burst -1;
						stopTime = stopTime+1;
						executeCycle++;
					}
					counter = counter + 1;
					if(counter == curArrive){
				
						if(ahead->burst < cur->burst){
							cur = ahead;
							executeCycle = 0;
						}else {

							if(cur->burst >0){
								executeCycle = 0;
							}else {
								if(cur->next != 0){
									cur->searched = -1;
									cur = ahead;
								}else {
									cur->searched = -1;
									lastCycle = 1;
								}
							}
						}
					
					}else {
						if(cur->burst > 0){
							executeCycle = 0;
						}else {
							if(cur->next != 0){
								cur->searched = -1;
								cur = ahead;
							}else {
							
								cur->searched = -1;
								lastCycle = 1;
							}
						}
					}
					printf("\t\t\t\t%d\n", stopTime);
					add_burst_time(&turnaround, stopTime);
					if(ahead->next != 0){
						ahead = ahead->next;
					}					
				}
			}


		}
	}else {
		printf("Nothing in the list\n");
	}
}	

void sjf_summary(struct times ** processes, struct times ** list){
	
	struct times * plist = *processes;
	struct times * awaitTimes = 0;
	struct times * turnaround =0;
	
	int curArrive = 0;
	int curBurst = 0;
	int counter = 0;
	int stopTime = 0;
	while(plist->next != 0){
		curArrive = find_by_index(list, plist->burst, 1);
		curBurst = find_by_index(list, plist->burst, 0);

		if(counter == 0){
			printf("P%d\t\t\t%d\t\t\t\t\%d\t\t\t\t%d\n", plist->burst + 1, curBurst, curArrive, curBurst);
			stopTime = curBurst;
		}else {

			printf("P%d\t\t\t%d\t\t\t\t\%d\t\t\t\t", plist->burst+ 1, curBurst, stopTime);
 			add_processes(&awaitTimes, stopTime - curArrive, curArrive);
			stopTime = stopTime + curBurst;

			printf("%d\n", stopTime);
		}
		plist = plist->next;
		counter++;
		
	}

	printf("P%d\t\t\t%d\t\t\t\t\%d\t\t\t\t", plist->burst+ 1, curBurst, stopTime);
	stopTime = stopTime + curBurst;

	printf("%d\n", stopTime);

}


void sjf_algorithm(struct times ** list){
	
	struct times * cur = *list;
	struct times * plist = 0;
	int counter = 0, searching = 1, incre = 0;
	int shorttes = 0;
	
	if(list != 0){
		listsort(list);
		//output_list(list);

		while(searching == 1){
			
			cur->searched = -1;
			if(counter > 0){
				shorttes = find_shortest_burst(list, counter);
			}else {
				shorttes = cur->arrival;
			}
			cur = get_shortest(list, counter);
			counter = counter + cur->burst;			

			if(cur == *list && incre > 1){
				searching = 0;
			}else {
				add_processes(&plist, shorttes, counter);
				searching = 1;
				cur = *list;
			}
			incre++;
		}
//		output_list(&plist);
		sjf_summary(&plist, list);
	}else {
		printf("Nothing in the list \n");
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
			srt_algorithm(list);
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
			// incomplete
			return 0;
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
		output_algorithm(&burstList, check, quanta);

	}else {
		printf("You didn't enter a valid algorithm. Process terminated!\n");		
	}
	
	return 0;
}

/**********************************************************************************************************************************
***********************************************************************************************************************************
***********************************************************************************************************************************/