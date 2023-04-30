/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:43:03 by abziouzi          #+#    #+#             */
/*   Updated: 2022/10/29 03:57:53 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (philo->philo_data->finished_flag != 1
		&& philo->death_flag != 1)
	{
		if (philo_life(philo) == 0)
			break ;
		if (philo->philo_data->philos_finished == philo->philo_data->nb_philos)
		{
			philo->philo_data->finished_flag = 1;
		}
	}
	return (NULL);
}

int	philo_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_data->forks[philo->left_fork]);
	philo_print_status(philo, TAKE_FORK_MSG);
	if (philo->philo_data->nb_philos == 1)
	{
		usleep(philo->philo_data->time_to_die * 1000);
		usleep(1000);
		return (0);
	}
	pthread_mutex_lock(&philo->philo_data->forks[philo->right_fork]);
	philo_print_status(philo, TAKE_FORK_MSG);
	philo_print_status(philo, EAT_MSG);
	usleep(philo->philo_data->time_to_eat * 1000);
	philo->last_meal = actual_time();
	philo->nb_meals++;
	if (philo->nb_meals == (unsigned int)philo->philo_data->nb_dishes)
		philo->philo_data->philos_finished++;
	pthread_mutex_unlock(&philo->philo_data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->philo_data->forks[philo->right_fork]);
	philo_print_status(philo, SLEEP_MSG);
	usleep(philo->philo_data->time_to_sleep * 1000);
	philo_print_status(philo, THINK_MSG);
	return (1);
}

void	*philo_check_death(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (philo->philo_data->finished_flag != 1)
	{
		if ((actual_time() - (philo->last_meal)) > \
			philo->philo_data->time_to_die)
		{
			philo_print_status(philo, DIE_MSG);
			philo->death_flag = 1;
			philo->philo_data->finished_flag = 1;
		}
		usleep(100);
	}
	return (NULL);
}
