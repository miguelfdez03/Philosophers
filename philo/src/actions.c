/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 17:55:58 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Función: take_fork_order
 * -----------------------
 * Determina el orden correcto para tomar los tenedores y evitar deadlock.
 * 
 * 1. Verifica si el filósofo tiene ID impar o par
 * 2. Los filósofos impares toman primero el tenedor izquierdo, luego el derecho
 * 3. Los filósofos pares toman primero el tenedor derecho, luego el izquierdo
 * 4. Esta estrategia evita deadlocks circulares entre filósofos adyacentes
 * 
 * philo: Puntero al filósofo que va a tomar los tenedores
 * first: Puntero donde se guardará la referencia al primer tenedor a tomar
 * second: Puntero donde se guardará la referencia al segundo tenedor a tomar
 * 
 * Retorna: Nada (void), modifica first y second por referencia
 */
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

/*
 * Función: take_forks
 * ------------------
 * El filósofo toma ambos tenedores necesarios para comer.
 * 
 * 1. Verifica si la simulación ha terminado antes de proceder
 * 2. Determina el orden correcto para tomar los tenedores (evita deadlock)
 * 3. Bloquea el primer tenedor e imprime mensaje
 * 4. Bloquea el segundo tenedor e imprime mensaje
 * 5. Ahora tiene ambos tenedores y puede proceder a comer
 * 
 * philo: Puntero al filósofo que va a tomar los tenedores
 * 
 * Retorna: Nada (void)
 */
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

/*
 * Función: eat
 * -----------
 * El filósofo come y actualiza su estado.
 * 
 * 1. Verifica si la simulación ha terminado antes de comer
 * 2. Si terminó, suelta los tenedores y sale
 * 3. Imprime el mensaje de que está comiendo
 * 4. Actualiza de forma thread-safe:
 *    - El tiempo de la última comida
 *    - El contador de comidas realizadas
 * 5. Espera el tiempo necesario para comer
 * 6. Suelta ambos tenedores al terminar
 * 
 * philo: Puntero al filósofo que va a comer
 * 
 * Retorna: Nada (void)
 */
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

/*
 * Función: sleep_and_think
 * -----------------------
 * El filósofo duerme y luego piensa antes del siguiente ciclo.
 * 
 * 1. Verifica si la simulación ha terminado antes de proceder
 * 2. Imprime el mensaje de que está durmiendo
 * 3. Espera durante el tiempo especificado para dormir
 * 4. Imprime el mensaje de que está pensando
 * 5. Si hay número impar de filósofos:
 *    - Calcula tiempo adicional de pensamiento
 *    - Esto ayuda a sincronizar mejor la simulación
 *    - Evita que algunos filósofos monopolicen los tenedores
 * 
 * philo: Puntero al filósofo que va a dormir y pensar
 * 
 * Retorna: Nada (void)
 */
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
