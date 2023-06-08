/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainHelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:07:44 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/25 13:55:37 by obelaizi         ###   ########.fr       */
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
	while (i < gnrl->num_phil)
	{
		gnrl->phls[i].id = i + 1;
		gnrl->phls[i].gnrl = gnrl;
		i++;
	}
	gnrl->mu_dead = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
	create_threads(gnrl);
}

int	check_death(t_phl *philo)
{
	int	curr_time;

	sem_wait(philo->mu_meal);
	curr_time = get_time(philo->gnrl->start_time) - philo->last_meal;
	if (curr_time >= philo->gnrl->tm_die)
	{
		sem_post(philo->mu_meal);
		sem_wait(philo->gnrl->prnt);
		printf("%d %d died\n", get_time(philo->gnrl->start_time), philo->id);
		sem_post(philo->gnrl->prnt);
		return (1);
	}
	sem_post(philo->mu_meal);
	return (0);
}

void	create_threads(t_gnrl *gnrl)
{
	int				i;
	struct timeval	tm;
	pthread_t		check_nm_eat;
	pid_t			pid;

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
		pid = fork();
		if (!pid)
			action(&gnrl->phls[i]);
		// pthread_create(&gnrl->phls[i].thread, NULL, &action, &gnrl->phls[i]);
	}
	if (gnrl->nm_eat != -1)
		pthread_create(&check_nm_eat, NULL, &number_eat, gnrl);
	waitpid(-1, NULL, 0);
	free_all(gnrl);
}
