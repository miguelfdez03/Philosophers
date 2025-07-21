/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:00:00 by miguel-f          #+#    #+#             */
/*   Updated: 2025/07/21 17:45:53 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Función: check_numeric_args
 * --------------------------
 * Verifica que todos los argumentos sean números positivos válidos.
 * 
 * 1. Recorre cada argumento desde el índice 1
 * 2. Verifica que cada carácter sea un dígito
 * 3. Convierte el argumento a entero y verifica que sea positivo
 * 4. Muestra mensaje de error si encuentra argumentos inválidos
 * 
 * argc: Número total de argumentos
 * argv: Array de strings con los argumentos
 * 
 * Retorna: 1 si todos los argumentos son válidos, 0 si hay error
 */
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

/*
 * Función: validate_args
 * ---------------------
 * Valida los argumentos de entrada del programa.
 * 
 * 1. Verifica que haya exactamente 4 o 5 argumentos
 * 2. Muestra el uso correcto si el número de argumentos es incorrecto
 * 3. Llama a check_numeric_args para verificar que sean números válidos
 * 
 * argc: Número total de argumentos
 * argv: Array de strings con los argumentos
 * 
 * Retorna: 1 si los argumentos son válidos, 0 si hay error
 */
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

/*
 * Función: main
 * ------------
 * Punto de entrada principal del programa philosophers.
 * 
 * 1. Valida los argumentos de entrada
 * 2. Inicializa la estructura de datos principal
 * 3. Inicia la simulación de los filósofos
 * 4. Limpia la memoria al finalizar
 * 5. Retorna código de salida apropiado
 * 
 * argc: Número total de argumentos
 * argv: Array de strings con los argumentos del programa
 * 
 * Retorna: 0 si todo fue exitoso, 1 en caso de error
 */
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
