/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 17:45:53 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Función: check_philosopher_death
 * -------------------------------
 * Verifica si algún filósofo ha muerto por no comer a tiempo.
 * 
 * 1. Recorre todos los filósofos uno por uno
 * 2. Para cada filósofo:
 *    - Calcula el tiempo transcurrido desde su última comida (thread-safe)
 *    - Compara con el tiempo máximo permitido sin comer
 * 3. Si encuentra un filósofo que murió:
 *    - Imprime el mensaje de muerte
 *    - Marca el final de la simulación
 *    - Retorna indicando que alguien murió
 * 
 * data: Puntero a la estructura principal de datos
 * 
 * Retorna: 1 si algún filósofo murió, 0 si todos están vivos
 */
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

/*
 * Función: check_all_eaten
 * -----------------------
 * Verifica si todos los filósofos han comido el número requerido de veces.
 * 
 * 1. Solo se ejecuta si se especificó un número mínimo de comidas
 * 2. Recorre todos los filósofos
 * 3. Para cada filósofo verifica (thread-safe) si ha comido suficiente
 * 4. Si encuentra alguno que no ha comido suficiente, retorna 0
 * 5. Si todos han comido suficiente:
 *    - Marca el final de la simulación
 *    - Retorna 1 indicando éxito
 * 
 * data: Puntero a la estructura principal de datos
 * 
 * Retorna: 1 si todos comieron suficiente, 0 si aún falta
 */
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

/*
 * Función: monitor_routine
 * -----------------------
 * Hilo monitor que supervisa continuamente el estado de la simulación.
 * 
 * 1. Ejecuta un bucle continuo mientras la simulación esté activa
 * 2. En cada iteración verifica:
 *    - Si algún filósofo ha muerto
 *    - Si todos han comido el número requerido (si aplica)
 * 3. Si cualquiera de las condiciones de fin se cumple, termina el bucle
 * 4. Espera un poco entre verificaciones para no saturar el CPU
 * 
 * arg: Puntero a la estructura t_data con los datos de la simulación
 * 
 * Retorna: NULL cuando termina la ejecución del hilo
 */
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
