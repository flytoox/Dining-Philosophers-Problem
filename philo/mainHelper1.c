/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainHelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:07:44 by obelaizi          #+#    #+#             */
/*   Updated: 2023/06/21 11:59:33 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	give_me_args(char **argv, int argc, t_gnrl *gnrl)
{
	int	x;
	int	i;

	i = 0;
	++argv;
	while (i < argc - 1)
	{
		x = ft_atoi(argv[i++]);
		if (x < 0)
			return (printf("We only accept positive int numbers ;)\n"), 1);
	}
	gnrl->num_phil = ft_atoi(argv[0]);
	if (!gnrl->num_phil)
		return (printf("0 philosophers??\n"), 1);
	gnrl->tm_die = ft_atoi(argv[1]);
	gnrl->tm_eat = ft_atoi(argv[2]);
	gnrl->tm_sleep = ft_atoi(argv[3]);
	if (argc == 6)
		gnrl->nm_eat = ft_atoi(argv[4]);
	else
		gnrl->nm_eat = -1;
	return (0);
}

int	init_var(t_gnrl *gnrl)
{
	int	i;

	i = 0;
	gnrl->phls = malloc(sizeof(t_phl) * gnrl->num_phil);
	gnrl->forks = malloc(sizeof(pthread_mutex_t) * gnrl->num_phil);
	if (!gnrl->phls || !gnrl->forks)
		return (1);
	while (i < gnrl->num_phil)
	{
		gnrl->phls[i].id = i + 1;
		gnrl->phls[i].gnrl = gnrl;
		pthread_mutex_init(&gnrl->forks[i], NULL);
		pthread_mutex_init(&gnrl->phls[i].mu_meal, NULL);
		pthread_mutex_init(&gnrl->phls[i].mu_nm_eat, NULL);
		i++;
	}
	pthread_mutex_init(&gnrl->mu_dead, NULL);
	return (create_threads(gnrl));
}

void	check_death_helper(t_gnrl *gnrl, int i)
{
	pthread_mutex_unlock(&gnrl->phls[i].mu_meal);
	pthread_mutex_lock(&gnrl->prnt);
	pthread_mutex_lock(&gnrl->mu_dead);
	if (!gnrl->dead)
	{
		pthread_mutex_unlock(&gnrl->mu_dead);
		pthread_mutex_unlock(&gnrl->prnt);
		return ;
	}
	gnrl->dead = 0;
	pthread_mutex_unlock(&gnrl->mu_dead);
	printf("%d %d died\n", get_time(gnrl->start_time), gnrl->phls[i].id);
	pthread_mutex_unlock(&gnrl->prnt);
}

void	*check_death(void *var)
{
	int		i;
	t_gnrl	*gnrl;

	i = 0;
	gnrl = (t_gnrl *)var;
	while (1)
	{
		i = i % gnrl->num_phil;
		pthread_mutex_lock(&gnrl->phls[i].mu_meal);
		pthread_mutex_lock(&gnrl->mu_dead);
		if (!gnrl->dead)
			return (pthread_mutex_unlock(&gnrl->mu_dead), NULL);
		pthread_mutex_unlock(&gnrl->mu_dead);
		if (get_time(gnrl->start_time) - gnrl->phls[i].last_meal
			>= gnrl->tm_die)
			return (check_death_helper(gnrl, i), NULL);
		pthread_mutex_unlock(&gnrl->phls[i++].mu_meal);
		usleep(200);
	}
}

int	create_threads(t_gnrl *gnrl)
{
	int	i;

	pthread_mutex_init(&gnrl->prnt, NULL);
	i = -1;
	gnrl->dead = 1;
	gnrl->start_time = time_now();
	while (++i < gnrl->num_phil)
	{
		gnrl->phls[i].last_meal = get_time(gnrl->start_time);
		gnrl->phls[i].nm_eat = gnrl->nm_eat;
		pthread_create(&gnrl->phls[i].thread, NULL, &action, &gnrl->phls[i]);
	}
	if (gnrl->nm_eat != -1)
		pthread_create(&gnrl->check_nm_eat, NULL, &number_eat, gnrl);
	pthread_create(&gnrl->check_dead, NULL, &check_death, gnrl);
	usleep(200);
	return (free_all(gnrl));
}
