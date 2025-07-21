/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:41:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 13:41:01 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	data->simulation_end = 0;
	data->start_time = get_time();
	if (!init_mutexes(data))
		return (0);
	if (!init_philosophers(data))
		return (0);
	return (1);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		printf("%s\n", ERR_MALLOC);
		return (0);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
		{
			printf("%s\n", ERR_MUTEX);
			return (0);
		}
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->meal_mutex, NULL) != 0
		|| pthread_mutex_init(&data->end_mutex, NULL) != 0)
	{
		printf("%s\n", ERR_MUTEX);
		return (0);
	}
	return (1);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		printf("%s\n", ERR_MALLOC);
		return (0);
	}
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

void	cleanup_data(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->end_mutex);
	if (data->philos)
		free(data->philos);
}
