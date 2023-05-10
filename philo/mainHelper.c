/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainHelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:13:03 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/10 18:19:32 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long long		result;
	int				i;

	result = 0;
	i = 0;
	while ((*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r') && *str)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && i < 10 && result < 2147483648)
			result = result * 10 + (str[i++] - 48);
		else
			return (-1);
	}
	return (result);
}

void	give_me_args(char **argv, int argc, t_gnrl *gnrl)
{
	int	x;
	int	i;

	i = 0;
	++argv;
	while (i < argc - 1)
	{
		x = ft_atoi(argv[i++]);
		if (x < 0)
			return (printf("We only accept positive int numbers ;)\n"), exit(1));
	}
	gnrl->num_phil = ft_atoi(argv[0]);
	gnrl->tm_die = ft_atoi(argv[1]);
	gnrl->tm_eat = ft_atoi(argv[2]);
	gnrl->tm_sleep = ft_atoi(argv[3]);
	if (argc == 6)
		gnrl->nm_eat = ft_atoi(argv[4]);
	else
		gnrl->nm_eat = -1;
}

void	init_var(t_gnrl *gnrl)
{
	int	i;

	i = 0;
	gnrl->phls = malloc(sizeof(t_phl) * gnrl->num_phil);
	gnrl->forks = malloc(sizeof(pthread_mutex_t) * gnrl->num_phil);
	while (i < gnrl->num_phil)
	{
		gnrl->phls[i].id = i + 1;
		gnrl->phls[i].gnrl = gnrl;
		i++;
	}
	pthread_mutex_init(&gnrl->mu_dead, NULL);
	create_threads(gnrl);
}

void	*number_eat(void	*var)
{
	t_gnrl	*gnrl;
	int		i;
	int		total;

	gnrl = (t_gnrl *) var;
	while (1)
	{
		total = 0;
		i = -1;
		while (++i < gnrl->num_phil)
			if (gnrl->phls[i].nm_eat == 0)
				total++;
		pthread_mutex_lock(&gnrl->prnt);
		if (total == gnrl->num_phil)
		{
			pthread_mutex_lock(&gnrl->mu_dead);
			gnrl->dead = 0;
			pthread_mutex_unlock(&gnrl->mu_dead);
			return (printf("%d every philosopher ate enough\n",
					get_time(gnrl->start_time)), free_all(gnrl), NULL);
		}
		pthread_mutex_unlock(&gnrl->prnt);
	}
	return (NULL);
}

void	check_death(t_gnrl *gnrl)
{
	int	i;
	int	curr_time;

	i = 0;
	while (1)
	{
		if (i == gnrl->num_phil)
			i = 0;
		pthread_mutex_lock(&gnrl->phls[i].mu_meal);
		curr_time = get_time(gnrl->start_time) - gnrl->phls[i].last_meal;
		pthread_mutex_unlock(&gnrl->phls[i].mu_meal);
		if (curr_time >= gnrl->tm_die)
		{
			pthread_mutex_lock(&gnrl->prnt);
			pthread_mutex_lock(&gnrl->mu_dead);
			gnrl->dead = 0;
			pthread_mutex_unlock(&gnrl->mu_dead);
			printf("%d %d died\n", get_time(gnrl->start_time), gnrl->phls[i].id);
			pthread_mutex_unlock(&gnrl->prnt);
			free_all(gnrl);
			exit(0);
		}
		i++;
	}
}
