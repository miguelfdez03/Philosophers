/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 13:39:53 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_data *data)
{
	int			i;
	long long	time_since_meal;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		time_since_meal = get_time() - data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->meal_mutex);
		if (time_since_meal >= data->time_to_die)
		{
			print_death(&data->philos[i]);
			set_simulation_end(data);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_eaten(t_data *data)
{
	int	i;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten < data->must_eat_count)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	set_simulation_end(data);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!simulation_ended(data))
	{
		if (check_philosopher_death(data) || check_all_eaten(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
