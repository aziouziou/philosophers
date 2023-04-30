/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 03:44:55 by abziouzi          #+#    #+#             */
/*   Updated: 2022/08/24 03:44:55 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	t_program	*program_data;

	program_data = malloc(sizeof(t_program));
	if (!program_data)
		philo_error(ERROR_MALLOC);
	if (arguments_scanner(argc, argv, program_data))
		run_program(program_data);
	else
		philo_error(ERROR_ARGS);
	return (0);
}

void	run_program(t_program *program_data)
{
	program_data->forks = malloc(sizeof(pthread_mutex_t) \
		* program_data->nb_philos);
	if (!program_data->forks)
		philo_error(ERROR_MALLOC);
	program_data->finished_flag = 0;
	program_data->philos_finished = 0;
	program_data->start_time = actual_time();
	mutex_init(program_data);
	run_philosophers(program_data);
}

void	run_philosophers(t_program *program_data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * program_data->nb_philos);
	if (!philos)
		philo_error(ERROR_MALLOC);
	while (i < program_data->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i +1) % program_data->nb_philos;
		philos[i].death_flag = 0;
		philos[i].last_meal = program_data->start_time;
		philos[i].nb_meals = 0;
		philos[i].philo_data = program_data;
		pthread_create(&philos[i].thread_id, NULL, &philo_routine, &philos[i]);
		pthread_create(&program_data->death_or_finish_thread, NULL, \
			&philo_check_death, &philos[i]);
		pthread_detach(program_data->death_or_finish_thread);
		usleep(100);
		i++;
	}
	join_threads(program_data, philos);
	terminate_program(program_data, philos);
}

void	terminate_program(t_program *program_data, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < program_data->nb_philos)
	{
		pthread_mutex_destroy(&program_data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program_data->write_mutex);
	free(program_data->forks);
	free(program_data);
	free(philosophers);
	printf("%sDestroying mutexes...\nFreeing memory...\
		\nClosing [./philo]...\n%s", LINES, LINES);
}

int	philo_error(char *str)
{
	printf("\033[34;01mError:\033[00m%s [./philo].\n", str);
	return (2);
}
