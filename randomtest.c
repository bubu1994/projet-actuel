
#include "philo.h"

size_t	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Erreur gettimeofday\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int main(void)
{
	int t = get_time_in_ms();
	printf("%d\n", t);
	return (0);
}