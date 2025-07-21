/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 13:39:53 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		print_action(philo, FORK_MSG, YELLOW);
		ft_usleep(philo->data->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!simulation_ended(philo->data))
	{
		take_forks(philo);
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
	{
		printf("%s\n", ERR_THREAD);
		return (0);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine,
				&data->philos[i]) != 0)
		{
			printf("%s\n", ERR_THREAD);
			set_simulation_end(data);
			break ;
		}
		i++;
	}
	pthread_join(monitor_thread, NULL);
	join_threads(data);
	return (1);
}
