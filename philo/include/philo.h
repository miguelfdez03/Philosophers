/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 12:51:25 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

/* Color codes for output */
# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"

/* Action messages */
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIED_MSG "died"

/* Error messages */
# define ERR_ARGS "Error: Invalid number of arguments"
# define ERR_INVALID "Error: Invalid argument"
# define ERR_MALLOC "Error: Memory allocation failed"
# define ERR_MUTEX "Error: Mutex initialization failed"
# define ERR_THREAD "Error: Thread creation failed"

/* Structures */
typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				simulation_end;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	end_mutex;
	t_philo			*philos;
}					t_data;

/* Function prototypes */

/* init.c */
int			init_data(t_data *data, int argc, char **argv);
int			init_mutexes(t_data *data);
int			init_philosophers(t_data *data);
void		cleanup_data(t_data *data);

/* philosopher.c */
void		*philosopher_routine(void *arg);
int			start_simulation(t_data *data);

/* monitor.c */
void		*monitor_routine(void *arg);
int			check_philosopher_death(t_data *data);
int			check_all_eaten(t_data *data);

/* actions.c */
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);

/* utils.c */
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strlen(const char *str);
long long	get_time(void);
void		ft_usleep(int milliseconds);
void		print_action(t_philo *philo, char *action, char *color);
void		print_death(t_philo *philo);
int			simulation_ended(t_data *data);
void		set_simulation_end(t_data *data);

#endif
