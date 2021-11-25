#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int SharedVariable = 0;
pthread_mutex_t lock;
void* SimpleThread(void *vargp);

int main(int argc, char *argv[]){
	if(pthread_mutex_init(&lock, NULL) != 0){
		printf("\n mutex init has failed\n");
		return 1;	
	}
	//Validate arg
	if(argc != 2){
		fprintf(stderr, "usage: a.out <int value>\n");
		return -1;
	}

	char *a = argv[1];
	int num = atoi(a);
	//Validate > 0
	if(num <= 0){
		fprintf(stderr, "%d must be >= 0\n", num);
		return - 1;
	}
	
	int i = 0;
	pthread_t tid;

	while( i < num){
	//	SimpleThread(i);	
		pthread_create(&tid, NULL, SimpleThread, (void *)&i);
		i++;
	}
	pthread_exit(NULL);
	printf("arg : %d\n" , num);
	pthread_mutex_destroy(&lock);
	return 0;
}

void* SimpleThread(void *vargp){
	pthread_mutex_lock(&lock);
	int* whichP = (int *) vargp;
	static int threadNum = 0;
	int which = threadNum;
	threadNum++;
	printf("Thread %d init\n", which);

	pthread_mutex_unlock(&lock);
		
	int num, val;
	usleep(25000); //Allow all threads to be init first
	for(num = 0; num < 20; num++){
		if(rand()>RAND_MAX/2){
			usleep(10);
			}
		pthread_mutex_lock(&lock);
		val = SharedVariable;
		printf("***thread %d sees value %d\n",which,val );
		SharedVariable = val + 1;
		pthread_mutex_unlock(&lock);
	}	

	while(val != (threadNum *20)){
		val = SharedVariable;
		//BLOCK UNTIL ALL THREADS EXEC
	}
	
	pthread_mutex_lock(&lock);
	val = SharedVariable;
	printf("Thread %d sees final value %d\n",which,val);
	pthread_mutex_unlock(&lock);
	 
}
