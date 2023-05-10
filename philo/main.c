/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:41:20 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/10 18:50:49 by obelaizi         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->gnrl->mu_dead);
	if (!philo->gnrl->dead)
		return (pthread_mutex_unlock(&philo->gnrl->mu_dead), 1);
	pthread_mutex_unlock(&philo->gnrl->mu_dead);
	pthread_mutex_lock(&philo->gnrl->prnt);
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
	if (i1 > philo->id % philo->gnrl->num_phil)
	{
		i1 = philo->id % philo->gnrl->num_phil;
		i2 = philo->id - 1;
	}
	pthread_mutex_lock(&philo->gnrl->forks[i1]);
	if (my_print("%d %d has taken fork\n", philo))
		return (1);
	pthread_mutex_lock(&philo->gnrl->forks[i2]);
	if (my_print("%d %d has taken fork\n", philo))
		return (1);
	if (my_print("%d %d is eating\n", philo))
		return (1);
	pthread_mutex_lock(&philo->mu_meal);
	philo->last_meal = get_time(philo->gnrl->start_time);
	pthread_mutex_unlock(&philo->mu_meal);
	usleep(philo->gnrl->tm_eat * 1000);
	pthread_mutex_unlock(&philo->gnrl->forks[i1]);
	pthread_mutex_unlock(&philo->gnrl->forks[i2]);
	return (0);
}

void	*action(void *phl)
{
	t_phl	*philo;

	philo = (t_phl *)phl;
	philo->nm_eat = philo->gnrl->nm_eat;
	if (philo->id % 2 == 0)
		usleep(philo->gnrl->tm_eat * 1000);
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
		usleep(philo->gnrl->tm_sleep * 1000);
		if (my_print("%d %d is thinking\n", philo))
			return (NULL);
	}
	return (NULL);
}

void	create_threads(t_gnrl *gnrl)
{
	int				i;
	struct timeval	tm;
	pthread_t		check_nm_eat;

	i = 0;
	while (i < gnrl->num_phil)
	{
		pthread_mutex_init(&gnrl->forks[i++], NULL);
		pthread_mutex_init(&gnrl->phls[i].mu_meal, NULL);
	}
	pthread_mutex_init(&gnrl->prnt, NULL);
	i = 0;
	gnrl->dead = 1;
	gettimeofday(&tm, NULL);
	gnrl->start_time = (tm.tv_usec / 1000) + (tm.tv_sec * 1000);
	while (i < gnrl->num_phil)
	{
		gnrl->phls[i].last_meal = get_time(gnrl->start_time);
		pthread_create(&gnrl->phls[i].thread, NULL, &action, &gnrl->phls[i]);
		i++;
	}
	if (gnrl->nm_eat != -1)
		pthread_create(&check_nm_eat, NULL, &number_eat, gnrl);
	check_death(gnrl);
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
