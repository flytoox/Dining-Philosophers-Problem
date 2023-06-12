/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainHelper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:07:44 by obelaizi          #+#    #+#             */
/*   Updated: 2023/06/12 20:15:08 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (!gnrl->num_phil)
		return (printf("0 philosophers??\n"), exit(1));
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
	create_threads(gnrl);
}

void	*check_death(void *phl)
{
	int		curr_time;
	t_phl	*philo;

	philo = (t_phl *)phl;
	while (1)
	{
		curr_time = get_time(philo->gnrl->start_time) - philo->last_meal;
		if (curr_time >= philo->gnrl->tm_die)
		{
			sem_wait(philo->gnrl->prnt);
			printf("%d %d died\n", get_time(philo->gnrl->start_time), philo->id);
			exit (0);
			sem_post(philo->gnrl->prnt);
		}
	}
	return (0);
}

void	create_threads(t_gnrl *gnrl)
{
	int				i;
	pid_t			pid;

	create_semaphores(gnrl);
	gnrl->start_time = time_now();
	i = -1;
	while (++i < gnrl->num_phil)
	{
		gnrl->phls[i].last_meal = get_time(gnrl->start_time);
		pid = fork();
		if (!pid)
			action(&gnrl->phls[i]);
	}
	usleep(500);
	free_all(gnrl);
}

char	*ft_itoa(int n)
{
	int		nb;
	char	*s;

	nb = count(n) + 1;
	s = malloc(nb + 1);
	if (!s)
		exit(1);
	s[0] = '/';
	if (!s)
		return (0);
	if (!n)
		s[1] = '0';
	if (n < 0)
	{
		s[1] = '-';
		n *= -1;
	}
	s[nb] = 0;
	while (n != 0)
	{
		s[--nb] = (n % 10) + 48;
		n /= 10;
	}
	return (s);
}
