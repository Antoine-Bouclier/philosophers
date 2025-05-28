#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
	struct timeval tv;
	struct timeval tv2;

	if (gettimeofday(&tv, NULL) == 0)
	{
		printf("Seconds: %ld\n", tv.tv_sec);
		printf("Microseconds: %ld\n", tv.tv_usec);
		long int start_time = (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
		printf("start time: %ld\n", start_time);
		usleep(10000);
		gettimeofday(&tv2, NULL);
		long int end_time = (tv2.tv_sec * 1000L) + (tv2.tv_usec / 1000L);
		printf("end time: %ld\n", end_time);
		long int difference = end_time - start_time;
		printf("difference: %ld\n", difference);
	}
	else
	{
		perror("gettimeofday");
	}
	return 0;
}
