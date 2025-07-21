/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:41:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 17:45:53 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Función: init_data
 * -----------------
 * Inicializa la estructura principal de datos con los argumentos del programa.
 * 
 * 1. Asigna los valores de tiempo y número de filósofos desde argv
 * 2. Establece el número mínimo de comidas (opcional)
 * 3. Inicializa el estado de la simulación y el tiempo de inicio
 * 4. Llama a las funciones para inicializar mutex y filósofos
 * 
 * data: Puntero a la estructura principal de datos
 * argc: Número total de argumentos
 * argv: Array de strings con los argumentos
 * 
 * Retorna: 1 si la inicialización fue exitosa, 0 en caso de error
 */
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

/*
 * Función: init_mutexes
 * --------------------
 * Inicializa todos los mutex necesarios para la simulación thread-safe.
 * 
 * 1. Asigna memoria para el array de mutex de tenedores
 * 2. Inicializa un mutex por cada tenedor (uno por filósofo)
 * 3. Inicializa los mutex de control: print, meal y end
 * 4. Maneja errores de asignación de memoria e inicialización
 * 
 * data: Puntero a la estructura principal de datos
 * 
 * Retorna: 1 si la inicialización fue exitosa, 0 en caso de error
 */
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

/*
 * Función: init_philosophers
 * -------------------------
 * Inicializa el array de filósofos y asigna tenedores a cada uno.
 * 
 * 1. Asigna memoria para el array de filósofos
 * 2. Para cada filósofo:
 *    - Asigna ID único (1 a n)
 *    - Inicializa contador de comidas en 0
 *    - Establece tiempo de última comida al inicio
 *    - Asigna tenedores izquierdo y derecho
 *    - Conecta con la estructura de datos principal
 * 
 * data: Puntero a la estructura principal de datos
 * 
 * Retorna: 1 si la inicialización fue exitosa, 0 en caso de error
 */
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

/*
 * Función: cleanup_data
 * --------------------
 * Libera toda la memoria asignada y destruye los mutex.
 * 
 * 1. Destruye todos los mutex de tenedores si existen
 * 2. Libera la memoria del array de tenedores
 * 3. Destruye los mutex de control (print, meal, end)
 * 4. Libera la memoria del array de filósofos
 * 5. Previene memory leaks al final del programa
 * 
 * data: Puntero a la estructura principal de datos
 * 
 * Retorna: Nada (void)
 */
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
