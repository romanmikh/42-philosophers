#include "philo.h"

// Return current time in milliseconds using timeval structure for precision
t_msec	get_current_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (-1);
	return (((long long)t.tv_sec * 1000) + ((long long)t.tv_usec / 1000));
}

// Pauses execution in 'large' chunks of time until specified time is reached
// Once 5ms are left, checks every millisecond to ensure we don't oversleep
void	wait_for_duration(t_msec waiting_time)
{
	t_msec	t;

	t = get_current_time();
	while (waiting_time - t > 5)
	{
		usleep(1000 * (waiting_time - t - 5));
		t = get_current_time();
	}
	while (waiting_time > t)
		t = get_current_time();
}
