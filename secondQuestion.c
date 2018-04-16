// ROLL - A13, NAME : DHEERAJ KUMAR , SECTION : K1645, ASSIGNED Q13
/*
		A barbershop consists of a waiting room with n chairs and a barber room with one barber chair. 
		If there are no customers to be served, the barber goes to sleep. If a customer enters the barbershop and 
		all chairs are occupied, then the customer leaves the shop. If the barber is busy but chairs are available, 
		then the customer sits in one of the free chairs. If the barber is asleep, the customer wakes up the barber. 
		Write a program to coordinate the barber and the customers.
*/

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h>
// The maximum number of customer threads. 
#define MAX_CUSTOMERS 25 

void *customer(void *num); 
void *barber(void *); 

// Sleep for a random time period
void randwait(int secs)
{ 
	// Generate an arbit number...
	int len = 1;
	sleep(len); 
}

// Initializing the semphore according to window system.
sem_t waitingRoom; 
sem_t barberChair; 
sem_t barberPillow; 
sem_t seatBelt;

//  tell that all proccess has done or not
int allDone = 0;

int main(int argc, char *argv[]) 
{
	// Get proccesss using pthread_t
	pthread_t btid; 
	pthread_t tid[MAX_CUSTOMERS]; 
	
	// numCustomers is number of customers
	// Number is array of maximum customers
	int i, x, numCustomers, numChairs; int Number[MAX_CUSTOMERS]; 
	
	
	// Scan the number of customers and the chair
	printf("Max customers can be 25.\n");
	printf("Enter number of customers and chairs : ");
	scanf("%d",&x);


	numCustomers = x; 
	scanf("%d",&x);
	numChairs = x;
	
	
	// When the number of customers are more than the maximum customer then pause.
	if (numCustomers > MAX_CUSTOMERS)
	{ 
		printf("The maximum number of Customers is %d.\n", MAX_CUSTOMERS); 
		system("PAUSE"); 
		return 0;
	} 
	
	printf("A solution to the sleeping barber problem using semaphores.\n"); 
	for (i = 0; i < MAX_CUSTOMERS; i++)
	{ 
		Number[i] = i; 
	} 
	
	// Initialize the semaphores with initial values... 
	sem_init(&waitingRoom, 0, numChairs); 
	sem_init(&barberChair, 0, 1);
	sem_init(&barberPillow, 0, 0); 
	sem_init(&seatBelt, 0, 0); 
 

	// Create the thread for barber with null function. 
	pthread_create(&btid, NULL, barber, NULL); 
 
	// Create the customers thread number of Customer times with customer method and num[i] value. 
	for (i = 0; i < numCustomers; i++) {
		pthread_create(&tid[i], NULL, customer, (void *)&Number[i]); 
	} 
 	// Join each of the threads to wait for them to finish. 
	for (i = 0; i < numCustomers; i++)
	{ 
 		pthread_join(tid[i],NULL); 
	} 
 	
	// When all of the customers are finished, kill the barber thread. 
	allDone = 1; 
	
	// Wake the barber so he will exit. 
	sem_post(&barberPillow);
	pthread_join(btid,NULL); 
	system("PAUSE"); 
	return 0;
}

void *customer(void *number)
{ 
	int num = *(int *)number; // Leave for the shop and take some random amount of time to arrive. 
	printf("Customer %d leaving for barber shop.\n", num); 
	
	randwait(5); 

	// Wait for space to open up in the waiting room... 
	printf("Customer %d arrived at barber shop.\n", num);
	sem_wait(&waitingRoom); 
 
	// Wait for the barber chair to become free. 
	printf("Customer %d entering waiting room.\n", num); 
	// The chair is free so give up your spot in the waiting room. 
	sem_wait(&barberChair); 
	
	// Wake up the barber... 
	sem_post(&waitingRoom); 
	printf("Customer %d waking the barber.\n", num); 
    
	
	// Wait for the barber to finish cutting your hair.
	sem_post(&barberPillow);
	// Give up the chair. 
	sem_wait(&seatBelt); 
	
	sem_post(&barberChair); 
	printf("Customer %d leaving barber shop.\n", num); 
}

void *barber(void *junk) 
{ 

	// While there are still customers to be serviced... Our barber is omnicient and can tell 
	//if there are customers still on the way to his shop. 
	
	// while each proccess is not going to be end
	while (!allDone)
	{
		// Sleep until someone arrives and wakes you.. 
		printf("The barber is sleeping\n"); 
 		sem_wait(&barberPillow); // Skip this stuff at the end... 
		
		if (!allDone) 
		{ 
			// Take a random amount of time to cut the customer's hair.
			printf("The barber is cutting hair\n"); 
			randwait(3);
			printf("The barber has finished cutting hair.\n"); // Release the customer when done cutting... 
			sem_post(&seatBelt);
		} 
 		else
		{
			printf("The barber is going home for the day.\n"); 
		} 
 	}
}
