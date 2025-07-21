/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 17:45:51 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Función: philosopher_routine
 * ---------------------------
 * Rutina principal que ejecuta cada filósofo en su hilo separado.
 * 
 * 1. Maneja el caso especial de un solo filósofo (que no puede comer)
 * 2. Los filósofos pares esperan un poco antes de empezar (evita competencia)
 * 3. Ejecuta el ciclo principal: tomar tenedores -> comer -> dormir -> pensar
 * 4. Continúa hasta que la simulación termine
 * 
 * arg: Puntero al struct t_philo del filósofo
 * 
 * Retorna: NULL cuando termina la ejecución del hilo
 */
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

/*
 * Función: join_threads
 * --------------------
 * Espera a que todos los hilos de filósofos terminen su ejecución.
 * 
 * 1. Itera a través de todos los filósofos
 * 2. Utiliza pthread_join para esperar que cada hilo termine
 * 3. Garantiza que todos los hilos terminen antes de continuar
 * 
 * data: Puntero a la estructura principal con todos los datos de la simulación
 * 
 * Retorna: Nada (void)
 */
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

/*
 * Función: start_simulation
 * ------------------------
 * Inicia la simulación completa creando y coordinando todos los hilos.
 * 
 * 1. Crea el hilo monitor que supervisa la simulación
 * 2. Crea un hilo para cada filósofo
 * 3. Si hay error en la creación, marca el final de la simulación
 * 4. Espera a que el monitor termine (indica fin de simulación)
 * 5. Espera a que todos los hilos de filósofos terminen
 * 
 * data: Puntero a la estructura principal con todos los datos de la simulación
 * 
 * Retorna: 1 si la simulación se ejecutó correctamente, 0 en caso de error
 */
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
