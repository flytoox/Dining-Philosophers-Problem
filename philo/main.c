/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:41:20 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/22 19:09:57 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(int start_time)
{
	struct timeval	tmp;
	int				curr_time;

	gettimeofday(&tmp, NULL);
	curr_time = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	return (curr_time - start_time);
}

int	my_print(const char *str, t_phl *philo)
{
	pthread_mutex_lock(&philo->gnrl->prnt);
	pthread_mutex_lock(&philo->gnrl->mu_dead);
	if (!philo->gnrl->dead)
	{
		pthread_mutex_unlock(&philo->gnrl->mu_dead);
		return (pthread_mutex_unlock(&philo->gnrl->prnt), 1);
	}
	pthread_mutex_unlock(&philo->gnrl->mu_dead);
	printf(str, get_time(philo->gnrl->start_time), philo->id);
	pthread_mutex_unlock(&philo->gnrl->prnt);
	return (0);
}

int	eating(t_phl *philo)
{
	int	i1;
	int	i2;

	i1 = philo->id - 1;
	i2 = philo->id % philo->gnrl->num_phil;
	pthread_mutex_lock(&philo->gnrl->forks[i1]);
	if (my_print("%d %d has taken fork\n", philo))
		return (pthread_mutex_unlock(&philo->gnrl->forks[i1]), 1);
	pthread_mutex_lock(&philo->gnrl->forks[i2]);
	if (my_print("%d %d has taken fork\n", philo))
	{
		pthread_mutex_unlock(&philo->gnrl->forks[i1]);
		return (pthread_mutex_unlock(&philo->gnrl->forks[i2]), 1);
	}
	if (my_print("%d %d is eating\n", philo))
	{
		pthread_mutex_unlock(&philo->gnrl->forks[i1]);
		return (pthread_mutex_unlock(&philo->gnrl->forks[i2]), 1);
	}
	pthread_mutex_lock(&philo->mu_meal);
	philo->last_meal = get_time(philo->gnrl->start_time);
	pthread_mutex_unlock(&philo->mu_meal);
	ft_usleep(philo->gnrl->tm_eat);
	pthread_mutex_unlock(&philo->gnrl->forks[i1]);
	return (pthread_mutex_unlock(&philo->gnrl->forks[i2]), 0);
}

void	*action(void *phl)
{
	t_phl	*philo;

	philo = (t_phl *)phl;
	philo->nm_eat = philo->gnrl->nm_eat;
	if (philo->id % 2 == 0)
		ft_usleep(philo->gnrl->tm_eat - 10);
	while (1)
	{
		pthread_mutex_lock(&philo->gnrl->mu_dead);
		if (!philo->gnrl->dead)
			return (pthread_mutex_unlock(&philo->gnrl->mu_dead), NULL);
		pthread_mutex_unlock(&philo->gnrl->mu_dead);
		if (eating(philo))
			return (NULL);
		if (philo->nm_eat > 0)
			philo->nm_eat--;
		if (my_print("%d %d is sleeping\n", philo))
			return (NULL);
		ft_usleep(philo->gnrl->tm_sleep);
		if (my_print("%d %d is thinking\n", philo))
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_gnrl	gnrl;

	if (argc != 6 && argc != 5)
		return (printf("Dude Arguments is sus\n"), 1);
	give_me_args(argv, argc, &gnrl);
	init_var(&gnrl);
	return (0);
}
