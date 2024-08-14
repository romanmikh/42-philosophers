/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:32:14 by rocky             #+#    #+#             */
/*   Updated: 2024/08/14 16:32:21 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Simulates the philosopher eating by picking up second fork + locks mutex
// Updates the last meal time & increments the eat count
// Philo needs to finish eating by time_to_die
// Updates time_to_die & waits till done eating
// Unlocks mutexes (puts forks down)
void	handle_eating(t_phil_stats *m)
{
	print_philo_action(m, 0);
	pthread_mutex_lock(m->secondfork);
	print_philo_action(m, 0);
	print_philo_action(m, 1);
	m->die_time = now() + m->p->time_to_die + m->p->time_to_eat;
	wait_for_duration(now() + m->p->time_to_eat);
	if (m->p->max_meal_num != -1)
		m->times_eaten += 1;
	pthread_mutex_unlock(m->secondfork);
	pthread_mutex_unlock(m->first_fork);
}

// Simulates sleeping by waiting for the sleep time to pass
void	handle_sleeping(t_phil_stats *m)
{
	print_philo_action(m, 2);
	wait_for_duration(now() + m->p->time_to_sleep);
}

// Simulates thinking by printing the thinking action (no waiting)
void	handle_thinking(t_phil_stats *m)
{
	print_philo_action(m, 3);
}

// Simulates dying by waiting until the death time is reached
void	handle_dying(t_phil_stats *m)
{
	wait_for_duration(m->die_time);
	print_philo_action(m, 4);
}
