#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static long shared_value = 0;
static long result = 0;

void* Thread_f(void *arg)
{
	int limit = *((int *) arg);
	
	result = 0;
	for(int i=0; i<limit; i++)
	{
		result = shared_value;
		result--;
		shared_value = result;
		//printf("result : %ld shared_value : %ld\n", result, shared_value);
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t t1, t2;
	int limit, s;

	limit = atoi(argv[1]);

	s = pthread_create(&t1, NULL, Thread_f, &limit);
	if(s!=0)
	{
		perror("pthread create");
	}
	
	s = pthread_create(&t2, NULL, Thread_f, &limit);
	if(s!=0)
	{
		perror("pthread create");
	}

	s = pthread_join(t1, NULL);
	if(s!=0)
	{
		perror("pthread_join");
	}

	s = pthread_join(t2, NULL);
	if(s!=0)
	{
		perror("pthread_join");
	}

	printf("%ld\n",shared_value);
	return 0;

}
