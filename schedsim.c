// C program for implementation of Simulation 
#include<stdio.h> 
#include<limits.h>
#include<stdlib.h>
#include "process.h"
#include "util.h"


// Function to find the waiting time for all processes
// Ref: https://tutorialspoint.dev/computer-science/operating-systems/program-round-robin-scheduling-set-1
void findWaitingTimeRR(ProcessType plist[], int n,int quantum) { 

  // Make a copy of burst times bt[] to store remaining burst times. 
  int burstTime[n]; 
  for (int i = 0 ; i < n ; i++) burstTime[i] =  plist[i].bt; 

  int clock = 0; // Current time 
  
  // Keep traversing processes in round robin manner until all of them are not done. 
  while (1) { 
    int allProcessesFinished = 1; 
  
    // Traverse all processes one by one repeatedly 
    for (int i = 0 ; i < n; i++) { 
      // If burst time of a process is greater than 0 then only need to process further 
      if (burstTime[i] > 0) { 
        allProcessesFinished = 0; // There is a pending process 

        if (burstTime[i] > quantum) { 
          // Increase the value of clock i.e. shows how much time a process has been processed 
          clock += quantum; 

          // Decrease the burst_time of current process by quantum 
          burstTime[i] -= quantum; 
        } 
          // If burst time is smaller than or equal to quantum. Last cycle for this process 
          else { 
          // Increase the value of t i.e. shows how much time a process has been processed 
          clock += burstTime[i]; 

          // Waiting time is current time minus time used by this process 
          plist[i].wt = clock - plist[i].bt; 

          // As the process gets fully executed make its remaining burst time = 0 
          burstTime[i] = 0; 
        } 
      } 
    } 

    // If all processes are done 
    if (allProcessesFinished) break; 
  } 
} 

// Function to find the waiting time for all  
// processes 
// Ref: https://www.geeksforgeeks.org/program-for-indexCurrShortestProcess-job-first-sjf-scheduling-set-2-preemptive/
void findWaitingTimeSJF(ProcessType plist[], int n) { 
  int burstTime[n]; 
  
  // Copy the burst time into burstTime[] for easy access to burst time of a process.
  for (int i = 0; i < n; i++) burstTime[i] = plist[i].bt; 

  int processesfinished = 0; // Indicator when done executing all processes.
  int clock = 0; // Current clock of process.
  int smallestBurstTime = INT_MAX; // The smallest burst time.
  int indexCurrShortestProcess = 0;
  int finish_time; 
  int foundProcessToExecute = 0; 

  // We need to execute all processes until each one is finished.
  // We step through 1 clock cycle at a time.
  while (processesfinished != n) { 

    // Find process with minimum remaining time among the 
    // processes that arrives till the current time
    for (int j = 0; j < n; j++) { 
      int foundSmallerBurstTime = (burstTime[j] < smallestBurstTime);
      int validBurstTime = (burstTime[j] > 0);
      int processCanStart = (plist[j].art <= clock);

      if (processCanStart && foundSmallerBurstTime && validBurstTime) { 
        smallestBurstTime = burstTime[j]; 
        indexCurrShortestProcess = j; 
        foundProcessToExecute = 1; 
      } 
    } 

    if (!foundProcessToExecute) { 
      clock++; 
      continue; 
    } 

    // Reduce remaining time by 1 simulating executing the process for this clock cycle.
    burstTime[indexCurrShortestProcess]--; 

    // Update minimum 
    smallestBurstTime = burstTime[indexCurrShortestProcess]; 
    if (smallestBurstTime == 0) smallestBurstTime = INT_MAX; 

    // If a process gets finished executing
    int processFinishedExecuting = (burstTime[indexCurrShortestProcess] == 0);
    if (processFinishedExecuting) { 
      // Increment finished 
      processesfinished++; 

      // Reset our check
      foundProcessToExecute = 0; 

      // Find finish time of current process 
      finish_time = clock + 1; 

      // Calculate this finished process waiting time 
      plist[indexCurrShortestProcess].wt = finish_time - 
                  plist[indexCurrShortestProcess].bt - 
                  plist[indexCurrShortestProcess].art; 

      // Error check
      int negativeWaitTime = (plist[indexCurrShortestProcess].wt < 0);
      if (negativeWaitTime) plist[indexCurrShortestProcess].wt = 0; 
    } 

    // Increment time 
    clock++; 
  } 
} 

// Function to find the waiting time for all  
// processes 
void findWaitingTime(ProcessType plist[], int n) { 
  // waiting time for first process is 0, or the arrival time if not 
  plist[0].wt = 0 +  plist[0].art; 

  // calculating waiting time 
  for (int  i = 1; i < n ; i++ ) 
      plist[i].wt =  plist[i-1].bt + plist[i-1].wt; 
} 
  
// Function to calculate turn around time 
void findTurnAroundTime( ProcessType plist[], int n) { 
  // calculating turnaround time by adding bt[i] + wt[i] 
  for (int  i = 0; i < n ; i++) 
      plist[i].tat = plist[i].bt + plist[i].wt; 
} 
  
// Function to sort the Process acc. to priority
int my_comparer(const void *this, const void *that) {

  // Cast into (ProcessType*)
  ProcessType* process1 = (ProcessType*) &this;
  ProcessType* process2 = (ProcessType*) &that;

  // Return 1 if this->pri < that->pri
  return (process1->pri < process2->pri);
} 

//Function to calculate average time 
void findavgTimeFCFS( ProcessType plist[], int n) { 
    //Function to find waiting time of all processes 
    findWaitingTime(plist, n); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nFCFS\n");
}

//Function to calculate average time 
void findavgTimeSJF( ProcessType plist[], int n) { 
    //Function to find waiting time of all processes 
    findWaitingTimeSJF(plist, n); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nSJF\n");
}

//Function to calculate average time 
void findavgTimeRR( ProcessType plist[], int n, int quantum) { 
    //Function to find waiting time of all processes 
    findWaitingTimeRR(plist, n, quantum); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nRR Quantum = %d\n", quantum);
}

//Function to calculate average time 
void findavgTimePriority( ProcessType plist[], int n) { 
  // Sort the processes by priority
  qsort(plist, sizeof(plist)/sizeof(plist[0]), sizeof(ProcessType), my_comparer);
	
  // Apply FCFS
  //Function to find waiting time of all processes 
  findWaitingTime(plist, n); 

  //Function to find turn around time for all processes 
  findTurnAroundTime(plist, n); 
  
  // Display processes along with all details 
  printf("\n*********\nPriority\n");
}

void printMetrics(ProcessType plist[], int n) {
  int total_wt = 0, total_tat = 0; 
  float awt, att;
  
  printf("\tProcesses\tBurst time\tWaiting time\tTurn around time\n"); 

  // Calculate total waiting time and total turn  
  // around time 
  for (int  i=0; i<n; i++) { 
    total_wt = total_wt + plist[i].wt; 
    total_tat = total_tat + plist[i].tat; 
    printf("\t%d\t\t%d\t\t%d\t\t%d\n", plist[i].pid, plist[i].bt, plist[i].wt, plist[i].tat); 
  } 

  awt = ((float)total_wt / (float)n);
  att = ((float)total_tat / (float)n);
  
  printf("\nAverage waiting time = %.2f", awt); 
  printf("\nAverage turn around time = %.2f\n", att); 
} 

ProcessType * initProc(char *filename, int *n) {
  FILE *input_file = fopen(filename, "r");
  if (!input_file) {
      fprintf(stderr, "Error: Invalid filepath\n");
      fflush(stdout);
      exit(0);
  }

  ProcessType *plist = parse_file(input_file, n);

  fclose(input_file);

  return plist;
}
  
// Driver code 
int main(int argc, char *argv[]) { 
  int n; 
  int quantum = 2;

  ProcessType *proc_list;

  if (argc < 2) {
      fprintf(stderr, "Usage: ./schedsim <input-file-path>\n");
      fflush(stdout);
      return 1;
    }
  
// FCFS
  n = 0;
  proc_list = initProc(argv[1], &n);

  findavgTimeFCFS(proc_list, n);
  
  printMetrics(proc_list, n);

// SJF
  n = 0;
  proc_list = initProc(argv[1], &n);
  
  findavgTimeSJF(proc_list, n); 
  
  printMetrics(proc_list, n);

// Priority
  n = 0; 
  proc_list = initProc(argv[1], &n);
  
  findavgTimePriority(proc_list, n); 
  
  printMetrics(proc_list, n);
  
// RR
  n = 0;
  proc_list = initProc(argv[1], &n);
  
  findavgTimeRR(proc_list, n, quantum); 
  
  printMetrics(proc_list, n);
  
  return 0; 
} 