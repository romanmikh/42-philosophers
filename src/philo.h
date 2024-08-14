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
	t_msec		start_time;
	int			max_meal_num;
}	t_cmds;

typedef struct s_phil_stats
{
	t_cmds			*p;
	int					id;
	t_msec				die_time;
	t_msec				eat_time;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*secondfork;
	pthread_mutex_t		times_eaten_m;
	int					times_eaten;
	pthread_mutex_t		*pr;
	struct s_thread_stats	*data;
}	t_phil_stats;

typedef struct s_thread_stats
{
	bool			is_dead;
	t_phil_stats		*philos;
	pthread_t		*threads;
	int				count;
	pthread_mutex_t	printing;
}	t_thread_stats;

enum	e_actions {
	e_fork = 0,
	e_eating = 1,
	e_sleeping = 2,
	e_thinking = 3,
	e_dead = 4
};

//time.c
t_msec	get_current_time(void);
void	wait_for_duration(t_msec waiting_time);
//format_converters.c
int		convert_str_to_int(const char *str, int *n);
int		validate_int(int sign, int *n);
int		convert_str_to_long_long(const char *str, t_msec *n);
int		validate_long_long(int sign, t_msec *n);
//utils.c
void	initialize_philosophers(t_phil_stats *philos, t_cmds *inpparams, int i);
int		initialize_philo_runner(t_thread_stats *philo_r, t_cmds *inpparams);
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

#endif
