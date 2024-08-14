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

typedef struct s_philo_p
{
	int			numofphilo;
	t_msec		timetodie;
	t_msec		timetoeat;
	t_msec		timetosleep;
	t_msec		timeatstart;
	int			numtoeat;
}	t_philo_p;

typedef struct s_philo_m
{
	t_philo_p			*p;
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
	struct s_philo_run	*data;
}	t_philo_m;

typedef struct s_philo_run
{
	bool			is_dead;
	t_philo_m		*philos;
	pthread_t		*threads;
	int				count;
	pthread_mutex_t	printing;
}	t_philo_run;

enum	e_print {
	e_fork = 0,
	e_eating = 1,
	e_sleeping = 2,
	e_thinking = 3,
	e_dead = 4
};

//time.c
t_msec	get_current_time(void);
void	wait_for_duration(t_msec waiting_time);
//my_atoi.c
int		convert_str_to_int(const char *str, int *n);
int		validate_int(int sign, int *n);
//my_atoll.c
int		convert_str_to_long_long(const char *str, t_msec *n);
int		validate_long_long(int sign, t_msec *n);
//philo_utils.c
void	initialize_philosophers(t_philo_m *philos, t_philo_p *inpparams, int i);
int		initialize_philo_runner(t_philo_run *philo_r, t_philo_p *inpparams);
void	print_philo_action(t_philo_m *m, enum e_print print);
void	cleanup_philo_runner(t_philo_run *philo_r);
//philo_run.c
int		philosopher_table_routine(t_philo_m *m);
void	*philosopher_thread_routine(void *philo);
void	create_philosopher_threads(t_philo_run *philo_r);
void	join_philosopher_threads(t_philo_run *philo_r);
//philo_actions.c
void	handle_eating(t_philo_m *m);
void	handle_sleeping(t_philo_m *m);
void	handle_thinking(t_philo_m *m);
void	handle_dying(t_philo_m *m);

#endif
