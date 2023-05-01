/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:41:20 by obelaizi          #+#    #+#             */
/*   Updated: 2023/04/27 08:13:33 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			return(printf("Dude don't enter something that not a number"), exit(1));
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

void	*action(void *phl)
{
	t_phl	*philo;

	philo = (t_phl *)phl;
	// while (1)
	{
		// pthread_mutex_lock(&philo->forks[philo->id - 1]);
		// printf("%lld has taken fork", philo->id);
		// pthread_mutex_lock(&philo->forks[philo->id]);
		// printf("%lld has taken fork", philo->id + 1);
		// pthread_mutex_unlock(&philo->forks[philo->id]);
		// pthread_mutex_unlock(&philo->forks[philo->id - 1]);
		
	}
}

void	create_threads(t_gnrl *gnrl)
{
	long long	i;

	i = 0;
	while (i < gnrl->num_phil)
	{
		pthread_mutex_init(&gnrl->phls->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < gnrl->num_phil)
	{
		pthread_create(&gnrl->phls[i].thread, NULL, &action, &gnrl->phls[i]);
		i++;
	}
	i = 0;
	while (i < gnrl->num_phil)
	{
		pthread_join(gnrl->phls[i].thread, NULL);
		i++;
	}
}

void	init_var(t_gnrl *gnrl)
{
	long long	i;

	i = 0;
	gnrl->phls = malloc(sizeof(t_phl) * gnrl->num_phil);
	gnrl->phls->forks = malloc(sizeof(pthread_mutex_t) * gnrl->num_phil);
	while (i < gnrl->num_phil)
	{
		gnrl->phls[i].time_to_die = gnrl->tm_die;
		gnrl->phls[i].id = i + 1;
		i++;
	}
	create_threads(gnrl);
}

// int	main(int argc, char **argv)
// {
// 	t_gnrl	gnrl;

// 	if (argc != 6 && argc != 5)
// 		return (printf("Dude Arguments is sus"), 1);
// 	give_me_args(argv, argc, &gnrl);
// 	init_var(&gnrl);
// }
typedef struct hh
{
	int	*forks;
}	bab;

typedef struct gg
{
	bab		*phls;
}	sab;


int main()
{
	sab tmp;

	tmp.phls = malloc(sizeof(bab) * 4);
	tmp.phls->forks = malloc(sizeof(int) * 4);
	tmp.phls[0].forks[0] = 5;
	printf("%d", tmp.phls[0].forks[0]);
}