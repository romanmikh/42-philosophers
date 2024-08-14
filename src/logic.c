#include "philo.h"

// Runs the main activity loop of each philo
// Pick up first fork so no other philo can use it simultaneously
// Check if enough time to finish eating before dying. If not, proceed to die
// After eating, check if enough time to sleep before dying. If not, dies
// If enough time, sleeps and then thinks
// int pthread_mutex_lock(pthread_mutex_t *mutex);, 
// mutex = "mutual exclusion" to shared resource, "grabs the key, reserving it"
int	philosopher_table_routine(t_philo_m *m)
{
	pthread_mutex_lock(m->first_fork);
	if (get_current_time() + m->p->timetoeat <= m->die_time
		&& (m->times_eaten < m->p->numtoeat || m->p->numtoeat == -1))
		handle_eating(m);
	else
	{
		pthread_mutex_unlock(m->first_fork);
		if (get_current_time() + m->p->timetoeat > m->die_time)
			handle_dying(m);
		return (0);
	}
	if (get_current_time() + m->p->timetosleep > m->die_time)
	{
		m->die_time -= m->p->timetoeat;
		handle_dying(m);
		return (0);
	}
	else
		handle_sleeping(m);
	handle_thinking(m);
	return (1);
}

// The routine function executed by each philosopher's thread
// Initialise die_time for each philo
// Even numbered philos wait 1 timetoeat before reaching for forks
// Starts infinite loop with time offset between odd and even philos
// Dinner aprty ends when someone dies or everyone has eaten enough
void	*philosopher_thread_routine(void *philo)
{
	t_philo_m	*m;

	m = (t_philo_m *)philo;
	m->die_time = m->p->timeatstart + m->p->timetodie;
	if (m->id % 2 == 0)
		wait_for_duration(get_current_time() + m->p->timetoeat);
	while (1)
	{
		if (philosopher_table_routine(m) == 0 || m->data->is_dead == 1)
			return (NULL);
	}
	return (NULL);
}

// Creates separate thread for each philo concurrently
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
// void *(*start_routine) (void *), void *arg);
// Creates new thread (program running independently within a larger one). 
// Passes a pointer to a routine function to execute when thread is created
void	create_philosopher_threads(t_philo_run *philo_r)
{
	int	i;

	i = 0;
	while (i < philo_r->count)
	{
		pthread_create(&philo_r->threads[i], NULL, philosopher_thread_routine,
			(void *)&philo_r->philos[i]);
		i++;
	}
}

// Ensures main program waits for all tgreads to finish
// int pthread_join(pthread_t thread, void **retval);
// Just waits for each thread to finish
void	join_philosopher_threads(t_philo_run *philo_r)
{
	int	i;

	i = 0;
	while (i < philo_r->count)
	{
		pthread_join(philo_r->threads[i], NULL);
		i++;
	}
}
