/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:40:42 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 17:45:53 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Función: ft_atoi
 * ---------------
 * Convierte una cadena de caracteres a un número entero.
 * 
 * 1. Inicializa el resultado en 0
 * 2. Recorre la cadena carácter por carácter
 * 3. Para cada dígito:
 *    - Multiplica el resultado actual por 10
 *    - Suma el valor numérico del dígito actual
 * 4. Se detiene al encontrar un carácter no numérico
 * 5. Retorna el número convertido
 * 
 * str: Cadena de caracteres que representa un número
 * 
 * Retorna: El número entero convertido desde la cadena
 */
int	ft_atoi(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

/*
 * Función: ft_isdigit
 * ------------------
 * Verifica si un carácter es un dígito numérico (0-9).
 * 
 * 1. Compara el carácter con el rango ASCII de dígitos
 * 2. Retorna verdadero si está entre '0' y '9'
 * 3. Retorna falso en cualquier otro caso
 * 
 * c: Carácter a verificar
 * 
 * Retorna: 1 si es dígito, 0 si no es dígito
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
 * Función: ft_strlen
 * -----------------
 * Calcula la longitud de una cadena de caracteres.
 * 
 * 1. Inicializa un contador en 0
 * 2. Recorre la cadena carácter por carácter
 * 3. Incrementa el contador por cada carácter encontrado
 * 4. Se detiene al encontrar el terminador nulo '\0'
 * 5. Retorna la cantidad total de caracteres
 * 
 * str: Cadena de caracteres a medir
 * 
 * Retorna: Número de caracteres en la cadena (sin incluir '\0')
 */
int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
