#include <pthread.h>
#include <stdio.h>

int sum;
void *runner(void *param);

int a = 0;//1st Fib num
int b = 1;//second Fib num

int main(int argc, char *argv[]){
	pthread_t tid;
	pthread_attr_t attr;
	
	if(argc != 2){
		fprintf (stderr, "usage: a.out <integer value>\n");
		return -1;
	}
	
	if(atoi (argv[1]) <= 0 ){
		fprintf(stderr, "%d must be greater than or 0\n",atoi(argv[1]));
		return -1;
	}
	//translate input to int
	int upper = atoi(argv[1]);

	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,runner,&upper);
	pthread_join(tid,NULL);
	printf(". . .\n");
}

void *runner(void *param){
	pthread_t tidc;
	int i=1;
	int* upper_p = (int*) param;//pointer for upper
	int upper = *upper_p; //deref upper
	int sendUpper = upper - 1;//upper for child
	sum = 0;
	if(upper > 1) {
		pthread_create(&tidc,NULL,runner,&sendUpper);
		pthread_join(tidc,NULL);
	}
	
	//based on values in a+b, get sum and print result
	if(upper == 1){
		printf(" 0");
		sum = 0;
		pthread_exit(0);
	} else if(upper == 2){
		printf(" 1");
		sum = 1;
		pthread_exit(0);
	} else {
		sum = a + b;
		a = b;
		b = sum;
	}
	printf(" %d", sum);
	pthread_exit(0);
}
