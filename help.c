# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/*
	The function passed to the thread must be returning a value.
	It doesn't have to have arguments.
*/
/* void	*routine()
{
	printf("Starting thread\n");
	sleep(3);
	printf("Ending thread\n");
} */

/*
	Here we create a routine to see what happens with race conditions.
	It will work with small values but not with bigger numbers.
	A race condition happens when:
	- Multiple threads access the same data
	- At the same time
	- And the result depends on who runs first
*/
int mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for(int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

/*
	A thread is a smaller unit of execution inside a process.
	Threads share the same memory of the process.
	Multiple threads can run at the same time (parallel work).
	They are often called “lightweight” compared to processes.
	You must be careful with race conditions (two threads modifying the same data at once),
	that's why we need to use mutex.
*/
int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	// To init 4 threads at once and then iterate through them, we can init like so :
	pthread_t	th[4];

	pthread_mutex_init(&mutex, NULL);

	/*
		Similar to creating a fork in processes.
		It returns 0 if it succeeds, otherwise it returns an error number,
		and the contents of *thread are undefined.
		The second arg here is used to customize the thread (eg. stack size). Using NULL
		is using the default settings.
		You can pass it a function to execute (arg 3) as well as its arguments (arg 4).
	*/
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);

	/*
		Similar to using the wait function in processes.
		It returns 0 if it succeeds, otherwise it returns an error number.
		The second argument is used to return a value from the thread, like a result.
		It can only return one value, but we can use a struct if we need more data.
		If no returned value is necessary, then we can pass NULL to it.
	*/
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	/*
		This is a way to create multiple threats at once.
		Don't use the thread join function here as it will cause issues.
		Better create another loop for it below.
	*/
	for(int i = 0; i < 4; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread.");
			return (1);
		}
	}

	for(int i = 0; i < 4; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Issue with thread.");
			return (2);
		}
	}

	pthread_mutex_destroy(&mutex);

	printf("Number of mails: %d\n", mails);
	return (0);
}
