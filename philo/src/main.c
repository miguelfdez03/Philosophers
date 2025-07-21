/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 13:49:57 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_numeric_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][0] == '\0')
			return (0);
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j++]))
			{
				printf("%s: %s\n", ERR_INVALID, argv[i]);
				return (0);
			}
		}
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("%s: %s must be positive\n", ERR_INVALID, argv[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	validate_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("%s\n", ERR_ARGS);
		printf("Usage: ./philo n_philos t_die t_eat t_sleep [num_eat]\n");
		return (0);
	}
	if (!check_numeric_args(argc, argv))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate_args(argc, argv))
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, argc, argv))
	{
		cleanup_data(&data);
		return (1);
	}
	if (!start_simulation(&data))
	{
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}
