/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:40:28 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 17:45:53 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Función: print_message
 * ---------------------
 * Imprime un mensaje con timestamp y formato específico del programa.
 * 
 * 1. Calcula el tiempo transcurrido desde el inicio de la simulación
 * 2. Imprime en formato: [color][timestamp] [id_filosofo] [accion][reset]
 * 3. Utiliza colores para diferenciar tipos de acciones
 * 4. El timestamp es relativo al inicio, no tiempo absoluto
 * 
 * philo: Puntero al filósofo que realiza la acción
 * action: String con la descripción de la acción
 * color: Código de color ANSI para la salida
 * 
 * Retorna: Nada (void)
 */
static void	print_message(t_philo *philo, char *action, char *color)
{
	long long	timestamp;

	timestamp = get_time() - philo->data->start_time;
	printf("%s%lld %d %s%s\n", color, timestamp, philo->id, action, RESET);
}

/*
 * Función: print_action
 * --------------------
 * Imprime una acción del filósofo de forma thread-safe.
 * 
 * 1. Bloquea el mutex de impresión para evitar salida mezclada
 * 2. Verifica que la simulación no haya terminado antes de imprimir
 * 3. Si la simulación continúa, llama a print_message
 * 4. Desbloquea el mutex de impresión
 * 5. Garantiza que solo se imprima una línea a la vez
 * 
 * philo: Puntero al filósofo que realiza la acción
 * action: String con la descripción de la acción
 * color: Código de color ANSI para la salida
 * 
 * Retorna: Nada (void)
 */
void	print_action(t_philo *philo, char *action, char *color)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!simulation_ended(philo->data))
		print_message(philo, action, color);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

/*
 * Función: print_death
 * -------------------
 * Imprime el mensaje de muerte de un filósofo de forma thread-safe.
 * 
 * 1. Bloquea el mutex de impresión para evitar salida mezclada
 * 2. Verifica que la simulación no haya terminado (condición de carrera)
 * 3. Si es seguro imprimir, muestra el mensaje de muerte en rojo
 * 4. Desbloquea el mutex de impresión
 * 5. Versión especializada de print_action para el evento crítico de muerte
 * 
 * philo: Puntero al filósofo que murió
 * 
 * Retorna: Nada (void)
 */
void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!simulation_ended(philo->data))
		print_message(philo, DIED_MSG, RED);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
