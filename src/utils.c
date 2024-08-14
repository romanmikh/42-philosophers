/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:39:14 by rocky             #+#    #+#             */
/*   Updated: 2024/08/14 17:34:49 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Sets up philo's ID, forks, and mutexes based on their position at the table
// Each philo is linked to overall simulation cmd_args from cmd
// Each philo has a left mutex fork, ensuring only one can use it at a time
// Last philo's left fork = 1st philo's right fork --> circular table
// Philos with odd ID pick up right forks, even IDs pick up left forks first
void	initialize_philosophers(t_phil_stats *philos, t_cmds *cmd_args, int i)
{
	philos->id = i;
	philos->times_eaten = 0;
	philos->p = cmd_args;
	pthread_mutex_init(&philos->left_fork, NULL);
	pthread_mutex_init(&philos->times_eaten_m, NULL);
	if (i + 1 == cmd_args->num_of_ph)
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
int	initialize_philo_runner(t_thread_stats *philo_r, t_cmds *cmd_args)
{
	int	i;

	philo_r->philos = malloc(sizeof(t_phil_stats) * cmd_args->num_of_ph);
	philo_r->threads = malloc(sizeof(pthread_t) * cmd_args->num_of_ph);
	philo_r->count = cmd_args->num_of_ph;
	philo_r->is_dead = 0;
	pthread_mutex_init(&philo_r->printing, NULL);
	if (!philo_r->philos || !philo_r->threads)
	{
		cleanup_philo_runner(philo_r);
		return (1);
	}
	i = 0;
	while (i < cmd_args->num_of_ph)
	{
		philo_r->philos[i].pr = &philo_r->printing;
		philo_r->philos[i].data = philo_r;
		initialize_philosophers(&philo_r->philos[i], cmd_args, i);
		i++;
	}
	return (0);
}

void	print_philo_action(t_phil_stats *m, enum e_actions pt)
{
	const char	*msg[] = {"ha cogido un tenedor", "esta comiendo",
		"esta durmiendo", "esta filosofando", "se ha palmao"};
	const char	*emoji[] = {"🍴", "🍝", "😴", "🤔", "💀"};

	pthread_mutex_lock(m->pr);
	if (m->data->is_dead != true && pt == 4)
	{
		printf(RED"%lld"CYA" %d "RESET"%s %s\n", now()
			- m->p->start, m->id + 1, msg[(int)pt], emoji[(int)pt]);
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
		printf(RED"%lld"CYA" %d "RESET"%s %s\n", now()
			- m->p->start, m->id + 1, msg[(int)pt], emoji[(int)pt]);
		pthread_mutex_unlock(m->pr);
	}
}

// Frees all allocated resources and destroys mutexes to clean u
void	cleanup_philo_runner(t_thread_stats *philo_r)
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
