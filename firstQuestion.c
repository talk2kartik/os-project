// ROLL - A13, NAME : DHEERAJ KUMAR , SECTION : K1645, ASSIGNED Q16 
/*
	Q)  	Design a scheduling program that is capable of scheduling many processes that comes in at some time 
	    interval and are allocated the CPU not more than 10 time units. CPU must schedule processes having short 
		execution time first. CPU is idle for 3 time units and does not entertain any process prior this time. 
		Scheduler must maintain a queue that keeps the order of execution of all the processes. Compute average 
		waiting and turnaround time.
*/
/*
Test case : 
	Enter total number of process : 4
	Enter Arrival Time and Burst Time for Process id 1 :0 9
	Enter Arrival Time and Burst Time for Process id 2 :1 5
	Enter Arrival Time and Burst Time for Process id 3 :2 3
	Enter Arrival Time and Burst Time for Process id 4 :3 4
	Enter Time Quantum:     5

	 Pid           tat               wt
	==================================
	 P2      |       9       |       4
	 P3      |       11      |       8
	 P4      |       14      |       10
	 P1      |       21      |       12
	================================
	 Total Waiting Time : 34
	 Total Turnarround Time : 55

	 Average Waiting Time : 34/4 => 8.50
	 Avg Turnaround Time : 55/4 => 13.75
	--------------------------------
*/



/* C Standard input output library */
#include<stdio.h> 
//  defining the maximum number of proccess that can be run
#define MAX 20

// main funtion where the real execution will be start
int main() 
{ 
	/*
		> declaring variable count to count the proccess or looping through proccess.
		> n will take input for number of proccess.
		> flag is  taken as flag bit to check a condtion.
		> timeQan is timeQuantum  which will entered by user.
	*/
	int count, j, n, time, remain, flag=0, timeQan; 
	
	/*
		> arrive_time array will store arrive time of each proccess
		> brust_time array will store brust time of each array
		> brust_copy is an array which will be same as brust_time but all the brust time
		  manipulation will be done on brust copy array
	*/
	int arrive_time[MAX], brust_time[10], brust_copy[MAX]; 
	
	// Take input from user , How many proccess wants to run
	printf("Enter total number of process : "); 
	scanf("%d",&n); 
	
	/*
		> Taking arrival time and brust time  inputs for n proccess number of time . 
		> arrival times of all procces are stored in arrive_time array .
		> brust time of all the procces stored in brust_time array .
	*/
	for(count=0;count<n;count++) 
	{ 
    	printf("Enter Arrival Time and Burst Time for Process id %d :",count+1); 
    	scanf("%d",&arrive_time[count]); 
    	
		// As we know we have  to decrement the brust time hence we are taking
		// an array rt in which we are copying the value of brust time
		scanf("%d",&brust_time[count]); 
    	brust_copy[count] = brust_time[count]; 
	} 
  	
	// Take input of time Quantum and store in variable timeQan
	printf("Enter Time Quantum:\t"); 
	scanf("%d",&timeQan); 

	// Copping number of proccess (n) into remain value to proccess it further to calculate values 
	remain = n; 
	
	// Declaring and initializing total waiting time (waitTime) and turnarround time (tatTime)
	int waitTime = 0, tatTime = 0;
	
	printf("\n\nPid\t      tat \t\twt\n\n"); 
	
	/*
		Loop will run from time zero to count =0 and if remain is not zero
		Here rt array is 
	*/
	printf("==================================\n");
	for(time=0,count=0;remain!=0;) 
  	{
  		
    	if(brust_copy[count] <= timeQan && brust_copy[count] > 0) 
    	{ 
    		// increment the time with current proccess
    		time+=brust_copy[count]; 
    		// make the brust time zero
			brust_copy[count]=0;
			// make flag as one so we can see below that proccess is done or not
			flag=1; 
    	}	 
    	else if(brust_copy[count] > 0) 
    	{
    		// As we proccessed the proccess then decrement the brust time with time quantum 
			brust_copy[count] -= timeQan; 
			// increment the time with given time quantum so we will check how muchh we have done
    		time += timeQan; 
    	} 
    	// If the proccess has zero brust time then print their values and make flag= 0  and continue the loop
		if(brust_copy[count]==0 && flag==1) 
    	{ 
    		
			// Hence one another proccess is proccessed so decrement the remain variable
			remain--; 
			
			// print the data of current proccess
			printf("P%d\t|\t%d\t|\t%d\n", count+1, time - arrive_time[count], time-arrive_time[count]-brust_time[count]); 
			
			// calcluate new total  > wait time
			waitTime += time - arrive_time[count] - brust_time[count]; 
			
			//calculate new total > turnarround time
    		tatTime += time-arrive_time[count]; 
			// make flag bit as 0
			flag=0; 
    	} 
    	// if count is equals to num of prroccess then count should start again
    	if(count == n-1) count=0; 
    	// else increment the count
    	else if(arrive_time[count+1] <= time) count++; 
    	else count=0;
	}
	printf("\n================================");
	
	// Printing the waiting time and trunaround time from above
	printf("\nTotal Waiting Time : %d\n",waitTime); 
	printf("\nTotal Turnarround Time : %d\n",tatTime);
	
	// Printing the average wating time
	printf("\nAverage Waiting Time : %d/%d => %.2f\n",waitTime,n,waitTime*1.0/n); 
	printf("Avg Turnaround Time : %d/%d => %.2f",tatTime,n,tatTime*1.0/n); 
	return 0;
}
