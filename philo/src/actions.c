/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 13:39:53 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork_order(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2 == 1)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (simulation_ended(philo->data))
		return ;
	take_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_action(philo, FORK_MSG, YELLOW);
	pthread_mutex_lock(second_fork);
	print_action(philo, FORK_MSG, YELLOW);
}

void	eat(t_philo *philo)
{
	if (simulation_ended(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_action(philo, EAT_MSG, GREEN);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep_and_think(t_philo *philo)
{
	int	think_time;

	if (simulation_ended(philo->data))
		return ;
	print_action(philo, SLEEP_MSG, BLUE);
	ft_usleep(philo->data->time_to_sleep);
	print_action(philo, THINK_MSG, CYAN);
	if (philo->data->num_philos % 2 == 1)
	{
		think_time = (philo->data->time_to_eat * 2
				- philo->data->time_to_sleep);
		if (think_time > 0)
			ft_usleep(think_time / 2);
	}
}
