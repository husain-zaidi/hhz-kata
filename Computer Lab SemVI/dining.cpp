#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>

#define N 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 

int state[N]; 
int phil[N] = { 0, 1, 2, 3, 4 }; 
int color[N] = { 0, 0, 0, 0, 0 };
int red = 3;
int blue = 3;  
sem_t mutex; 
sem_t S[N]; 


void test(int pNum) 
{ 
	if (state[pNum] == HUNGRY && (red >= 2 || blue >= 2)) { 
		// state that eating 
		state[pNum] = EATING; 
		if(red >= 2){
			color[pNum] = 1;
			red -= 2;
		}else {
			color[pNum] = 0;
			blue -= 2;
		}

		sleep(2); 
		if(color[pNum] == 1)
			printf("Philosopher %d takes 2 forks (Color: red) \n", pNum + 1); 
		else
			printf("Philosopher %d takes 2 forks (Color: blue) \n", pNum + 1);

		printf("Philosopher %d is Eating\n", pNum + 1); 

		sem_post(&S[pNum]); 
	} 
} 

// take up chopsticks 
void take_fork(int pNum) 
{ 

	sem_wait(&mutex); 

	// state that hungry 
	state[pNum] = HUNGRY; 

	printf("Philosopher %d is Hungry\n", pNum + 1); 

	// eat 
	test(pNum); 

	sem_post(&mutex); 
	sem_wait(&S[pNum]); 

	sleep(1); 
} 

// put down chopsticks 
void put_fork(int pNum) 
{ 

	sem_wait(&mutex); 

	// state that thinking 
	state[pNum] = THINKING; 

	if(color[pNum] == 1)
		red += 2;
	else
		blue += 2;

	if(color[pNum] == 1)
		printf("Philosopher %d puts 2 forks (Color: red) \n", pNum + 1); 
	else
		printf("Philosopher %d puts 2 forks (Color: blue) \n", pNum + 1);
	
	printf("Philosopher %d is thinking\n", pNum + 1); 

	for(int i = pNum+1; i < N; i++)
		test(i);
	for(int i = 0; i < pNum; i++)
		test(i);
	
	sem_post(&mutex); 
} 

void* philospher(void* num) 
{ 

	while (1) { 
		int* i = num; 
		sleep(1); 
		take_fork(*i); 
		sleep(0); 
		put_fork(*i); 
	} 
} 

int main() 
{
	int i; 
	pthread_t thread_id[N]; 

	// initialize the semaphores 
	sem_init(&mutex, 0, 1); 

	for (i = 0; i < N; i++) 
		sem_init(&S[i], 0, 0); 

	for (i = 0; i < N; i++) { 
		// create philosopher processes 
		pthread_create(&thread_id[i], NULL, philospher, &phil[i]); 
		printf("Philosopher %d is thinking\n", i + 1); 
	} 

	for (i = 0; i < N; i++) 
		pthread_join(thread_id[i], NULL); 
} 
