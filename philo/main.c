/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:41:20 by obelaizi          #+#    #+#             */
/*   Updated: 2023/04/10 21:03:04 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	*give_me_args(char **argv, int argc)
{
	long long	x;
	long long	*args;
	int			i;

	args = malloc(sizeof(long long) * (argc - 1));
	i = 0;
	while (i < argc - 1)
	{
		x = ft_atoi(*++argv);
		if (x == -1)
			return (printf("Dude don't enter something that not a number"), exit(1), NULL);
		args[i++] = x;
	}
	return (args);
}

// void	philo_5(t_gnrl gnrl)
// {

// }

// void	philo_6(t_gnrl gnrl)
// {

// }

void	*function(void *philo)
{

	return (NULL);
}

int	main(int argc, char **argv)
{
	t_gnrl		gnrl;
	t_phl		*philos;
	long long	i;

	if (argc != 6 && argc != 5)
		return (printf("Dude Arguments is sus"), 1);
	gnrl.args = give_me_args(argv, argc);
	philos = malloc(sizeof(philos) * gnrl.args[0]);
	// if (argc == 5)
	// 	philo_5(gnrl);
	// else	
	// 	philo_6(gnrl);
	gettimeofday(&gnrl.time, NULL);
	i = 0;
	while (i < gnrl.args[0])
	{
		philos[i].id = i + 1;
		pthread_create(&philos[i].thread, NULL, &function, &philos[i]);
		i++;
	}

}
