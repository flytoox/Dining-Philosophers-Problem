/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainHelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:13:03 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/07 22:18:39 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	int				sign;
	long long		result;

	result = 0;
	sign = 1;
	while ((*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r') && *str)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			result = result * 10 +(*str - 48);
		else
			return (-1);
		str++;
	}
	return (result * sign);
}

void	give_me_args(char **argv, int argc, t_gnrl *gnrl)
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
			return (printf("Dude don't enter a number"), exit(1));
		args[i++] = x;
	}
	gnrl->num_phil = args[0];
	gnrl->tm_die = args[1];
	gnrl->tm_eat = args[2];
	gnrl->tm_sleep = args[3];
	if (argc == 6)
		gnrl->nm_eat = args[4];
	else
		gnrl->nm_eat = -1;
}

void	init_var(t_gnrl *gnrl)
{
	long long	i;

	i = 0;
	gnrl->phls = malloc(sizeof(t_phl) * gnrl->num_phil);
	gnrl->forks = malloc(sizeof(pthread_mutex_t) * gnrl->num_phil);
	while (i < gnrl->num_phil)
	{
		gnrl->phls[i].id = i + 1;
		gnrl->phls[i].gnrl = gnrl;
		i++;
	}
	create_threads(gnrl);
}

void	check_death(t_gnrl *gnrl)
{
	long long	i;
	long long	curr_time;

	i = 0;
	while (1)
	{
		curr_time = get_time(gnrl->start_time);
		if (i == gnrl->num_phil - 1)
			i = 0;
		if (curr_time - gnrl->phls[i].last_meal >= gnrl->tm_die)
		{
			my_print("%lld %lld died\n", &gnrl->phls[i]);
			exit(1);
		}
		i++;
	}
}
