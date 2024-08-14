#include "philo.h"

// Sets up philo's ID, forks, and mutexes based on their position at the table
// Each philo is linked to overall simulation inpparams from cmd
// Each philo has a left mutex fork, ensuring only one can use it at a time
// Last philo's left fork = 1st philo's right form --> circular table
// Philos with odd ID pick up right forks, even IDs pick up left forks first
void	initialize_philosophers(t_philo_m *philos, t_philo_p *inpparams, int i)
{
	philos->id = i;
	philos->times_eaten = 0;
	philos->p = inpparams;
	pthread_mutex_init(&philos->left_fork, NULL);
	pthread_mutex_init(&philos->times_eaten_m, NULL);
	if (i + 1 == inpparams->numofphilo)
		philos->right_fork = &(philos - i)->left_fork;
	else
		philos->right_fork = &(philos + 1)->left_fork;
	philos->first_fork = &philos->left_fork;
	philos->secondfork = philos->right_fork;
	if (i % 2)
	{
		philos->first_fork = philos->right_fork;
		philos->secondfork = &philos->left_fork;
	}
}

// Allocating memory, initializing philosophers, and setting up mutexes
int	initialize_philo_runner(t_philo_run *philo_r, t_philo_p *inpparams)
{
	int	i;

	philo_r->philos = malloc(sizeof(t_philo_m) * inpparams->numofphilo);
	philo_r->threads = malloc(sizeof(pthread_t) * inpparams->numofphilo);
	philo_r->count = inpparams->numofphilo;
	philo_r->is_dead = 0;
	pthread_mutex_init(&philo_r->printing, NULL);
	if (!philo_r->philos || !philo_r->threads)
	{
		cleanup_philo_runner(philo_r);
		return (1);
	}
	i = 0;
	while (i < inpparams->numofphilo)
	{
		philo_r->philos[i].pr = &philo_r->printing;
		philo_r->philos[i].data = philo_r;
		initialize_philosophers(&philo_r->philos[i], inpparams, i);
		i++;
	}
	return (0);
}

void	print_philo_action(t_philo_m *m, enum e_print print)
{
	const char	*msg[] = {
		"has taken a fork", "is eating", "is sleeping",
		"is thinking", "died"};
	const char	*emoji[] = {
		"🍴", "🍝", "😴", "🤔", "💀"};

	pthread_mutex_lock(m->pr);
	if (m->data->is_dead != true && print == 4)
	{
		printf("\033[1;32m%lld \033[0m\033[1;34m%d\033[0m %s %s\n", get_current_time() - m->p->timeatstart, m->id + 1,
			msg[(int)print], emoji[(int)print]);
		m->data->is_dead = true;
		pthread_mutex_unlock(m->pr);
		return ;
	}
	else if (m->data->is_dead == true)
	{
		pthread_mutex_unlock(m->pr);
		return ;
	}
	else
	{
		printf("\033[1;32m%lld \033[0m\033[1;34m%d\033[0m %s %s\n", get_current_time() - m->p->timeatstart, m->id + 1,
			msg[(int)print], emoji[(int)print]);
		pthread_mutex_unlock(m->pr);
	}
}

// Frees all allocated resources and destroys mutexes to clean up after the simulation ends
void	cleanup_philo_runner(t_philo_run *philo_r)
{
	int	i;

	i = 0;
	while (i < philo_r->count)
	{
		pthread_mutex_destroy(&philo_r->philos[i].times_eaten_m);
		pthread_mutex_destroy(&philo_r->philos[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&philo_r->printing);
	free(philo_r->philos);
	free(philo_r->threads);
}

