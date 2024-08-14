#include "philo.h"

// Simulates the philosopher eating by picking up second fork + locks mutex
// Updates the last meal time & increments the eat count
// Philo needs to START (not finish) eating by timetodie
// Updates timetodie & waits till done eating
// Unlocks mutexes (puts forks down)
void	handle_eating(t_philo_m *m)
{
	print_philo_action(m, 0);
	pthread_mutex_lock(m->secondfork);
	print_philo_action(m, 0);
	print_philo_action(m, 1);
	m->die_time = get_current_time() + m->p->timetodie + m->p->timetoeat;
	wait_for_duration(get_current_time() + m->p->timetoeat);
	if (m->p->numtoeat != -1)
		m->times_eaten += 1;
	pthread_mutex_unlock(m->secondfork);
	pthread_mutex_unlock(m->first_fork);
}

// Simulates sleeping by waiting for the sleep time to pass
void	handle_sleeping(t_philo_m *m)
{
	print_philo_action(m, 2);
	wait_for_duration(get_current_time() + m->p->timetosleep);
}

// Simulates thinking by printing the thinking action (no waiting)
void	handle_thinking(t_philo_m *m)
{
	print_philo_action(m, 3);
}

// Simulates dying by waiting until the death time is reached
void	handle_dying(t_philo_m *m)
{
	wait_for_duration(m->die_time);
	print_philo_action(m, 4);
}

