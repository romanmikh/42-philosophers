/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:33:08 by rocky             #+#    #+#             */
/*   Updated: 2024/08/14 16:35:42 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_input_error_msg(void)
{
	printf("Input Error. Correct format:"
		"\n arg1: program_name number_of_philosophers"
		"\n arg2:time_to_die \n arg3: time_to_eat \n arg4: time_to_sleep"
		"\n optional arg5: number_of_times_each_philosopher_must_eat\n");
}

// Parses and saves command-line arguments to input parameters structure
// Sets max_meal_num to -1, so infinite unless specified by user
// Checka cmd args + their types, and num_of_ph != 0
int	parse_and_save_args(int argc, char **argv, t_cmds *inpparams)
{
	inpparams->max_meal_num = -1;
	if (argc != 6 && argc != 5)
		return (1);
	if (convert_str_to_int(argv[1], &inpparams->num_of_ph))
		return (1);
	if (convert_str_to_long_long(argv[2], &inpparams->time_to_die))
		return (1);
	if (convert_str_to_long_long(argv[3], &inpparams->time_to_eat))
		return (1);
	if (convert_str_to_long_long(argv[4], &inpparams->time_to_sleep))
		return (1);
	if (argc == 6)
	{
		if (convert_str_to_int(argv[5], &inpparams->max_meal_num))
			return (1);
	}
	if (inpparams->num_of_ph == 0 || inpparams->max_meal_num == 0)
		return (1);
	return (0);
}

/*
 * 1. Parse and validate input
 * 2. Handle input errors
 * 3. Initialise simulation
 * 4. Single philosopher edge case (picks up one fork, dies lmao)
 * 5. Create threads
 * 6. Wait for threads to finish
 * 7. Clean up resources
*/
int	main(int argc, char **argv)
{
	t_thread_stats	philo_r;
	t_cmds			inpparams;

	if (parse_and_save_args(argc, argv, &inpparams))
	{
		print_input_error_msg();
		return (0);
	}
	inpparams.start = now();
	initialize_philo_runner(&philo_r, &inpparams);
	if (inpparams.num_of_ph == 1)
	{
		print_philo_action(philo_r.philos, 0);
		wait_for_duration(inpparams.start + inpparams.time_to_die);
		printf("%lld %d died\n", now() - inpparams.start, 1);
		return (0);
	}
	create_philosopher_threads(&philo_r);
	join_philosopher_threads(&philo_r);
	cleanup_philo_runner(&philo_r);
	return (0);
}
