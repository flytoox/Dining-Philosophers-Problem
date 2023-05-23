/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainHelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:07:44 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/23 19:23:06 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	gnrl->mu_dead = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
	create_threads(gnrl);
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
		sem_wait(gnrl->phls[i].mu_meal);
		curr_time = get_time(gnrl->start_time) - gnrl->phls[i].last_meal;
		if (curr_time >= gnrl->tm_die)
		{
			sem_post(gnrl->phls[i].mu_meal);
			sem_wait(gnrl->prnt);
			sem_wait(gnrl->mu_dead);
			gnrl->dead = 0;
			sem_post(gnrl->mu_dead);
			printf("%d %d died\n", get_time(gnrl->start_time), gnrl->phls[i].id);
			sem_post(gnrl->prnt);
			free_all(gnrl);
			exit(0);
		}
		sem_post(gnrl->phls[i].mu_meal);
		i++;
	}
}

void	create_threads(t_gnrl *gnrl)
{
	int				i;
	struct timeval	tm;
	pthread_t		check_nm_eat;

	i = -1;
	while (++i < gnrl->num_phil)
		gnrl->phls[i].mu_meal = sem_open("/meal", O_CREAT | O_EXCL, 0644, 1);
	gnrl->forks = sem_open("/my_sem", O_CREAT | O_EXCL, 0644, gnrl->num_phil);
	gnrl->prnt = sem_open("/prnt", O_CREAT | O_EXCL, 0644, 1);
	i = -1;
	gnrl->dead = 1;
	gettimeofday(&tm, NULL);
	gnrl->start_time = (tm.tv_usec / 1000) + (tm.tv_sec * 1000);
	while (++i < gnrl->num_phil)
	{
		gnrl->phls[i].last_meal = get_time(gnrl->start_time);
		pthread_create(&gnrl->phls[i].thread, NULL, &action, &gnrl->phls[i]);
	}
	if (gnrl->nm_eat != -1)
		pthread_create(&check_nm_eat, NULL, &number_eat, gnrl);
	usleep((gnrl->tm_die - 20));
	check_death(gnrl);
}
