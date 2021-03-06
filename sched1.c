/**
*
*	Name:		Matthew Saliba
*	Desc:		CSCI212 - Ass 2: Task 1
*	S #:		3284165
*	Sub:		CSCI212
*	Mod:		
*	Note:		Handles min of 4 processes - BUG
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct times {
	int value;
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

// output summary for struct: times list
void output_summary(char value[50], struct times ** list, int startIncre){

	
	printf("\n");
	printf("%s\n", value);
	struct times * temp;
	temp = *list;
	
	if(temp != 0){
		while(temp->next != 0){
			printf("P%d\t\t%d\n", startIncre, temp->value);
			startIncre++;
			temp = temp->next;
		}
		printf("P%d\t\t%d\n", startIncre, temp->value);
	}
	
	printf("\n");

}

// output summary for struct: summary list
void output_rr_summary(char value[50], struct summary ** list){

	printf("\n");
	printf("%s\n", value);
	struct summary * temp;
	temp = *list;
	
	if(temp != 0){
		while(temp->next != 0){
			printf("P%d\t\t%d\n", temp->pid, temp->time);
			temp = temp->next;
		}
		printf("P%d\t\t%d\n", temp->pid, temp->time);
	}
	
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

// add values to list pointer - struct: times
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

// add values to struct: summary
void add_summary_list(struct summary ** list, int new_pid, int new_time){
	
	struct summary * temp, *r;
	temp = * list;
	
	if(temp == 0){
		temp = ((struct summary *) malloc(sizeof(struct summary)));
		temp->pid = new_pid;
		temp->time = new_time;
		temp->next = 0;
		*list = temp;
	}else {
		while(temp->next != 0){
			temp = temp->next;
		}
		r = ((struct summary *)malloc(sizeof(struct summary)));
		r->pid = new_pid;
		r->time = new_time;
		r->next = 0;
		temp->next = r;
	}
	
}

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


// marks the shortest number with a minus -1;
void mark_shortest(struct times ** list, int index){
	
	struct times * temp;
	temp = *list;
	int counter = 0;
	
	while(temp->next != 0){
		if(counter == index){
			temp->value = -1;
		}
		counter = counter + 1;
		temp = temp->next;
	}
	if(counter == index){
		temp->value = -1;
	}
	
}

// finds the shortest number and marks the number with a -1
int findshortest(struct times ** list){

	struct times * temp;
	temp = *list;
	int shortest = 9999;
	int shortLocate = 0;
	int counter = 0;
	int found = 0;
	
	while(temp->next != 0){
			
		if(temp->value != -1){
			if(temp->value < shortest){
				shortest = temp->value;
				shortLocate = counter;
				found = 1;
			}
		}
		counter = counter + 1;
		temp = temp->next;
	}
	if(temp->value != -1){
		if(temp->value < shortest){
			shortest = temp->value;
			shortLocate = counter;
			found = 1;
		}
	}
		mark_shortest(list, shortLocate);	

	if(found > 0){

		return shortest;
	}else {
		return -1;
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

/**********************************************************************************************************************************
***********************************************************************************************************************************
***********************************************************************************************************************************/


/***********************************************************************************************************************************
******************************************************** ALGORITHMS ****************************************************************
***********************************************************************************************************************************/

// outputs the values based on the Round Robin values (RR)

void rr_algorithm(struct times ** list, int quanta){
	
	if(quanta > 0){
		struct times * temp;
		
		temp = *list;
		
		struct summary * wait = 0;
		struct summary * turnaround = 0;
		char waitMessage[50] = { "Computing Wait times\n" };
		char summaryMessage[50] = { "Computing Turn around times\n" };
		int processCounter = 1, scheduling = 1, time = 0, finished = 0, burst = 0, start = 0;
	
		if(temp == 0){
			printf("Nothing in the list\n");
		}else {
	
			while(scheduling == 1){
				while(temp->next != 0){
					
					if(temp->value != -1){
						if(temp->value - quanta > 0){
							time = time + 2;
							burst = temp->value;
							add_summary_list(&turnaround, processCounter, time);
							printf("P%d\t\t\t\%d\t\t\t\t%d\t\t\t\t%d\n", processCounter, burst, start, time);
							add_summary_list(&wait, processCounter, start);
							start = start + 2;
							temp->value = temp->value - quanta;
							if(finished == 0){
								finished = 1;
							}
						}else {
							time = time + temp->value;
							burst = temp->value;
							add_summary_list(&turnaround, processCounter, time);
							printf("P%d\t\t\t\%d\t\t\t\t%d\t\t\t\t%d\n", processCounter, burst, start, time);
							start = start + temp->value;
							add_summary_list(&wait, processCounter, start);

							temp->value = -1;
						}
					}
					processCounter++;
					temp = temp->next;
				}
				if(temp->value != -1){
					if(temp->value - quanta > 0){
						time = time + 2;
						burst = temp->value;
						add_summary_list(&turnaround, processCounter, time);
						printf("P%d\t\t\t\%d\t\t\t\t%d\t\t\t\t%d\n", processCounter, burst, start, time);
						add_summary_list(&wait, processCounter, start);
						start = start + 2;

						temp->value = temp->value - quanta;
						if(finished == 0){
							finished = 1;
						}
					}else {
						time = time + temp->value;
						burst = temp->value;
						add_summary_list(&turnaround, processCounter, time);
						printf("P%d\t\t\t\%d\t\t\t\t%d\t\t\t\t%d\n", processCounter, burst, start, time);
						start = start + temp->value;
						add_summary_list(&wait, processCounter, start);
						temp->value = -1;
					}
				}
				if(finished == 0){
					scheduling = 0;
				}else {
					processCounter = 1;
					finished = 0;
					temp = *list;
				}

			}
		}
		output_rr_summary(waitMessage, &wait);
		output_rr_summary(summaryMessage, &turnaround);
		
		printf("\n");
	}else {
		printf("Quanta time must be greater than 0\n");
	}
}

// outputs the values based on the FCFS algorithm

void fcfs_algorithm(struct times ** list){

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

	int processCounter = 1, startTime = 0, stopTime = 0, searching = 1, curShort = 0, counter = 0;	
	struct times * visited = 0;
	struct times * temp;
	struct times * wait = 0;
	struct times * turnaround = 0;
	char waitMessage[50] = { "Computing Wait times\n" };
	char summaryMessage[50] = { "Computing Turn around times\n" };
	
	temp = *list;
	
	if(temp == 0){
		printf("Nothing in the list\n");
	}else {

		while(searching == 1){
			
			curShort = findshortest(list);
			if(curShort == -1){
				searching = 0;
			}else {
				stopTime = stopTime + curShort;
				add_burst_time(&wait, startTime);
				add_burst_time(&turnaround, stopTime);
				printf("P%d\t\t\t%d\t\t\t\t\%d\t\t\t\t%d\n", counter, curShort, startTime, stopTime);
				startTime = startTime + curShort;
				
			}
			counter++;
		}
	}
	counter = 1;
	output_summary(waitMessage, &wait, counter);
	counter = 1;
	output_summary(summaryMessage, &turnaround, counter);
	
	printf("\n");
}

//outputs the values based on the SRT algorithm
// this is the same as the sjf as the arrival time is the same i.e 0
void srt_algorithm(struct times ** list){
	
	sjf_algorithm(list);
	
	printf("\n");
}


/***********************************************************************************************************************************
******************************************************** ALGORITHMS ****************************************************************
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
			rr_algorithm(list, quanta);
		break;
 	}

}


/**********************************************************************************************************************************
****************************************************** MAIN **********************************************************************
***********************************************************************************************************************************/

int main(){

	char algor[10];
	// value for quanta - RR only
	int quanta = 0, check = 0, timeRetrieve = 1, processCount = 1, tempNum = 0;
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
			if(processCount <= 63){
				printf("Process %d (P%d) – What is the burst time?\n",processCount, processCount);
			
				scanf("%d", &tempNum);
				if (!feof(stdin)){
					add_burst_time(&burstList, tempNum);
				}else {
					printf("Input terminated\n");
					timeRetrieve = 0;
				}
			}else {
				timeRetrieve = 0;
				fclose(stdin);
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