/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 02:36:01 by abziouzi          #+#    #+#             */
/*   Updated: 2022/10/29 02:48:42 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_atoi(char *arg)
{
	unsigned int	i;
	unsigned int	res;
	int				neg;

	i = 0;
	res = 0;
	neg = 1;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == 32)
		i++;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			neg = -neg;
		i++;
	}
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		res = res * 10 + arg[i] - '0';
		i++;
	}
	if (neg < 0 && res >= 2147483647)
		return (philo_error(ERROR_ARG));
	else if (res >= 2147483648)
		return (philo_error(ERROR_ARG));
	return (res * neg);
}

long int	actual_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		philo_error(ERROR_TIME);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	philo_print_status(t_philo *philo, char *status)
{
	long int	time;

	time = actual_time() - philo->philo_data->start_time;
	pthread_mutex_lock(&philo->philo_data->write_mutex);
	if (philo->philo_data->finished_flag == 0)
		printf("\033[33m%ld %s%d \033[32m%s\033[0m", time, PHILOSOPHER \
			, philo->id, status);
	pthread_mutex_unlock(&philo->philo_data->write_mutex);
}
