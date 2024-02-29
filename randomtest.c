
#include "philo.h"

int main(void)
{
	struct timeval	temps_actuel;
	int	res = gettimeofday(&temps_actuel, NULL);
	printf("sec: %ld\nmicrosec: %d\n", temps_actuel.tv_sec, temps_actuel.tv_usec);
	return (0);
}