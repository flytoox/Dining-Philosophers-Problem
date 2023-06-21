/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:41:20 by obelaizi          #+#    #+#             */
/*   Updated: 2023/06/20 19:45:40 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_time(int start_time)
{
	struct timeval	tmp;
	int				curr_time;

	gettimeofday(&tmp, NULL);
	curr_time = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	return (curr_time - start_time);
}

void	my_print(const char *str, t_phl *philo)
{
	sem_wait(philo->gnrl->prnt);
	printf(str, get_time(philo->gnrl->start_time), philo->id);
	sem_post(philo->gnrl->prnt);
}

void	eating(t_phl *philo)
{
	int	i1;
	int	i2;

	i1 = philo->id - 1;
	i2 = philo->id % philo->gnrl->num_phil;
	sem_wait(philo->gnrl->forks);
	my_print("%d %d has taken fork\n", philo);
	sem_wait(philo->gnrl->forks);
	my_print("%d %d has taken fork\n", philo);
	my_print("%d %d is eating\n", philo);
	sem_wait(philo->sm_lst_meal);
	philo->last_meal = get_time(philo->gnrl->start_time);
	sem_post(philo->sm_lst_meal);
	ft_usleep(philo->gnrl->tm_eat);
	sem_post(philo->gnrl->forks);
	sem_post(philo->gnrl->forks);
}

void	action(void *phl)
{
	t_phl	*philo;
	int		engh_eat;
	char	*tmp;

	philo = (t_phl *)phl;
	tmp = ft_itoa(__INT_MAX__ - philo->id);
	sem_unlink(tmp);
	philo->sm_lst_meal = sem_open(tmp, O_CREAT | O_EXCL, 0666, 1);
	free(tmp);
	engh_eat = 0;
	if (philo->id % 2 == 0)
		usleep(300);
	pthread_create(&philo->thread, NULL, &check_death, philo);
	pthread_detach(philo->thread);
	while (1)
	{
		eating(philo);
		if (philo->gnrl->nm_eat != -1 && philo->gnrl->nm_eat == ++engh_eat)
			sem_post(philo->num_eat);
		my_print("%d %d is sleeping\n", philo);
		ft_usleep(philo->gnrl->tm_sleep);
		my_print("%d %d is thinking\n", philo);
	}
}

int	main(int argc, char **argv)
{
	t_gnrl	gnrl;

	if (argc != 6 && argc != 5)
		return (printf("Dude Arguments are sus\n"), 1);
	give_me_args(argv, argc, &gnrl);
	init_var(&gnrl);
	return (0);
}
