/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 02:21:45 by abziouzi          #+#    #+#             */
/*   Updated: 2022/10/29 02:21:45 by abziouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//	Including standard libraries

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

//	Defining Errors & Messages

# define ERROR_ARG		"Invalid argument for"
# define ERROR_ARGS		"Invalid argument(s) for"
# define ERROR_MALLOC	"Malloc failed for"
# define ERROR_MUTEX	"Mutex creation failed for"
# define ERROR_THREAD	"Thread creation failed for"
# define ERROR_TIME		"Time creation failed for"

# define PHILOSOPHER	"\033[37m> Philosopher \033[35m"
# define DIE_MSG 		"\033[31mdied.\n\033[0m"
# define EAT_MSG 		"is eating.\n"
# define SLEEP_MSG		"is sleeping.\n"
# define TAKE_FORK_MSG	"has taken a fork.\n"
# define THINK_MSG		"is thinking.\n"
# define LINES			"---------------------\n"

//	Structs

typedef struct s_program
{
	int				nb_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				nb_dishes;
	int				finished_flag;
	int				philos_finished;

	long int		start_time;

	pthread_t		death_or_finish_thread;

	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;

}				t_program;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				death_flag;

	long int		last_meal;

	unsigned int	nb_meals;

	pthread_t		thread_id;

	t_program		*philo_data;
}				t_philo;

//	philo_main.c

void		run_program(t_program *program_data);
void		run_philosophers(t_program *program_data);
void		terminate_program(t_program *program_data, t_philo *philosophers);

int			philo_error(char *str);

//	philo_parser.

int			arguments_scanner(int argc, char *argv[], t_program *program_data);
int			argument_processor(char *argv[], int i, int j);

void		mutex_init(t_program *program_data);
void		join_threads(t_program *program_data, t_philo *philosophers);

//	philo_routine.

int			philo_life(t_philo *philo);

void		*philo_routine(void *param);
void		*philo_check_death(void *param);

//	philo_utils.

int			philo_atoi(char *arg);

long int	actual_time(void);

void		philo_print_status(t_philo *philo, char *status);

#endif
