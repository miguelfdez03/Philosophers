/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:40:28 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 13:40:29 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_message(t_philo *philo, char *action, char *color)
{
	long long	timestamp;

	timestamp = get_time() - philo->data->start_time;
	printf("%s%lld %d %s%s\n", color, timestamp, philo->id, action, RESET);
}

void	print_action(t_philo *philo, char *action, char *color)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!simulation_ended(philo->data))
		print_message(philo, action, color);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!simulation_ended(philo->data))
		print_message(philo, DIED_MSG, RED);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
