#include "philo.h"

void	print_input_error_msg(void)
{
	printf("Input Error. Correct format:"
		"\n arg1: program_name number_of_philosophers"
		"\n arg2:time_to_die \n arg3: time_to_eat \n arg4: time_to_sleep"
		"\n optional arg5: number_of_times_each_philosopher_must_eat\n");
}

// Parses and saves command-line arguments to input parameters structure
// Sets numtoeat to -1, so infinite unless specified by user
// Checka cmd args + their types, and numofphilo != 0
int	parse_and_save_args(int argc, char **argv, t_philo_p *inpparams)
{
	inpparams->numtoeat = -1;
	if (argc != 6 && argc != 5)
		return (1);
	if (convert_str_to_int(argv[1], &inpparams->numofphilo))
		return (1);
	if (convert_str_to_long_long(argv[2], &inpparams->timetodie))
		return (1);
	if (convert_str_to_long_long(argv[3], &inpparams->timetoeat))
		return (1);
	if (convert_str_to_long_long(argv[4], &inpparams->timetosleep))
		return (1);
	if (argc == 6)
	{
		if (convert_str_to_int(argv[5], &inpparams->numtoeat))
			return (1);
	}
	if (inpparams->numofphilo == 0 || inpparams->numtoeat == 0)
		return (1);
	return (0);
}

/*
1. Parse and validate input
2. Handle input errors
3. Initialise simulation
4. Single philosopher edge case (picks up one fork, dies lmao)
5. Create threads
6. Wait for threads to finish
7. Clean up resources
*/
int	main(int argc, char **argv)
{
	t_philo_p	inpparams;
	t_philo_run	philo_r;

	if (parse_and_save_args(argc, argv, &inpparams))
	{
		print_input_error_msg();
		return (0);
	}
	inpparams.timeatstart = get_current_time();
	initialize_philo_runner(&philo_r, &inpparams);
	if (inpparams.numofphilo == 1)
	{
		print_philo_action(philo_r.philos, 0);
		wait_for_duration(inpparams.timeatstart + inpparams.timetodie);
		printf("%lld %d died\n", get_current_time() - inpparams.timeatstart, 1);
		return (0);
	}
	create_philosopher_threads(&philo_r);
	join_philosopher_threads(&philo_r);
	cleanup_philo_runner(&philo_r);
	return (0);
}
