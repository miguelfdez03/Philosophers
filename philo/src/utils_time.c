/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:40:47 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 17:45:53 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Función: get_time
 * ----------------
 * Obtiene el tiempo actual en milisegundos desde la época Unix.
 * 
 * 1. Utiliza gettimeofday para obtener tiempo con precisión de microsegundos
 * 2. Convierte segundos a milisegundos (multiplica por 1000)
 * 3. Convierte microsegundos a milisegundos (divide por 1000)
 * 4. Suma ambos valores para obtener el tiempo total en milisegundos
 * 5. Retorna el timestamp completo
 * 
 * Retorna: Tiempo actual en milisegundos como long long
 */
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
 * Función: ft_usleep
 * -----------------
 * Función de espera más precisa que sleep() para intervalos en milisegundos.
 * 
 * 1. Obtiene el tiempo de inicio
 * 2. Entra en un bucle de espera activa
 * 3. En cada iteración:
 *    - Verifica cuánto tiempo ha pasado
 *    - Si ya pasó el tiempo requerido, sale del bucle
 *    - Si no, hace una pausa corta con usleep(500)
 * 4. Proporciona mayor precisión que sleep() estándar
 * 
 * milliseconds: Número de milisegundos a esperar
 * 
 * Retorna: Nada (void)
 */
void	ft_usleep(int milliseconds)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}

/*
 * Función: simulation_ended
 * ------------------------
 * Verifica de forma thread-safe si la simulación ha terminado.
 * 
 * 1. Bloquea el mutex de control de fin de simulación
 * 2. Lee el valor de la variable simulation_end de forma segura
 * 3. Desbloquea el mutex
 * 4. Retorna el estado leído
 * 5. Garantiza acceso seguro desde múltiples hilos
 * 
 * data: Puntero a la estructura principal de datos
 * 
 * Retorna: 1 si la simulación terminó, 0 si continúa
 */
int	simulation_ended(t_data *data)
{
	int	ended;

	pthread_mutex_lock(&data->end_mutex);
	ended = data->simulation_end;
	pthread_mutex_unlock(&data->end_mutex);
	return (ended);
}

/*
 * Función: set_simulation_end
 * --------------------------
 * Marca el final de la simulación de forma thread-safe.
 * 
 * 1. Bloquea el mutex de control de fin de simulación
 * 2. Establece la variable simulation_end en 1 de forma segura
 * 3. Desbloquea el mutex
 * 4. Notifica a todos los hilos que la simulación debe terminar
 * 5. Garantiza modificación segura desde cualquier hilo
 * 
 * data: Puntero a la estructura principal de datos
 * 
 * Retorna: Nada (void)
 */
void	set_simulation_end(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->end_mutex);
}
