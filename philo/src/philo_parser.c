/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:18:33 by abziouzi          #+#    #+#             */
/*   Updated: 2022/10/29 02:21:17 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	arguments_scanner(int argc, char *argv[], t_program *program_data)
{
	if ((argc == 5 || argc == 6) && argument_processor(argv, 1, 0))
	{
		program_data->nb_philos = philo_atoi(argv[1]);
		program_data->time_to_die = philo_atoi(argv[2]);
		program_data->time_to_eat = philo_atoi(argv[3]);
		program_data->time_to_sleep = philo_atoi(argv[4]);
		program_data->nb_dishes = -1;
		if (argc == 6)
			program_data->nb_dishes = philo_atoi(argv[5]);
		return (1);
	}
	return (0);
}

int	argument_processor(char *argv[], int i, int j)
{
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9'
		|| argv[i][0] == '-')
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	mutex_init(t_program *program_data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&program_data->write_mutex, NULL);
	while (i < program_data->nb_philos)
	{
		pthread_mutex_init(&program_data->forks[i], NULL);
		i++;
	}
}

void	join_threads(t_program *program_data, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < program_data->nb_philos)
	{
		pthread_join(philosophers[i].thread_id, NULL);
		i++;
	}
}
