/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:47:20 by rocky             #+#    #+#             */
/*   Updated: 2024/08/14 17:47:30 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef long long	t_msec;

typedef struct s_cmds
{
	int			num_of_ph;
	t_msec		time_to_die;
	t_msec		time_to_eat;
	t_msec		time_to_sleep;
	t_msec		start;
	int			max_meal_num;
}	t_cmds;

typedef struct s_phil_stats
{
	struct s_thread_stats			*data;
	pthread_mutex_t					*right_fork;
	pthread_mutex_t					*first_fork;
	pthread_mutex_t					*secondfork;
	pthread_mutex_t					times_eaten_m;
	pthread_mutex_t					*pr;
	pthread_mutex_t					left_fork;
	t_msec							die_time;
	t_msec							eat_time;
	t_cmds							*p;
	int								id;
	int								times_eaten;
}	t_phil_stats;

typedef struct s_thread_stats
{
	bool			is_dead;
	t_phil_stats	*philos;
	pthread_t		*threads;
	int				count;
	pthread_mutex_t	printing;
}	t_thread_stats;

enum	e_actions
{
	e_fork = 0,
	e_eating = 1,
	e_sleeping = 2,
	e_thinking = 3,
	e_dead = 4
};

//time.c
t_msec	now(void);
void	wait_for_duration(t_msec waiting_time);
//format_converters.c
int		convert_str_to_int(const char *str, int *n);
int		validate_int(int sign, int *n);
int		convert_str_to_long_long(const char *str, t_msec *n);
int		validate_long_long(int sign, t_msec *n);
//utils.c
void	initialize_philosophers(t_phil_stats *philos, t_cmds *cmd_args, int i);
int		initialize_philo_runner(t_thread_stats *philo_r, t_cmds *cmd_args);
void	print_philo_action(t_phil_stats *m, enum e_actions print);
void	cleanup_philo_runner(t_thread_stats *philo_r);
//logic.c
int		philosopher_table_routine(t_phil_stats *m);
void	*philosopher_thread_routine(void *philo);
void	create_philosopher_threads(t_thread_stats *philo_r);
void	join_philosopher_threads(t_thread_stats *philo_r);
//handle_actions.c
void	handle_eating(t_phil_stats *m);
void	handle_sleeping(t_phil_stats *m);
void	handle_thinking(t_phil_stats *m);
void	handle_dying(t_phil_stats *m);

# define RESET "\033[0m"

# define BLK "\033[0;30m"
# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m"
# define CYA "\033[0;36m"
# define WHI "\033[0;37m"

# define B_BLK "\033[1;30m"
# define B_RED "\033[1;31m"
# define B_GRN "\033[1;32m"
# define B_YEL "\033[1;33m"
# define B_BLU "\033[1;34m"
# define B_MAG "\033[1;35m"
# define B_CYA "\033[1;36m"
# define B_WHI "\033[1;37m"

#endif
