/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:40:47 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 13:40:48 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int milliseconds)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}

int	simulation_ended(t_data *data)
{
	int	ended;

	pthread_mutex_lock(&data->end_mutex);
	ended = data->simulation_end;
	pthread_mutex_unlock(&data->end_mutex);
	return (ended);
}

void	set_simulation_end(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->end_mutex);
}
