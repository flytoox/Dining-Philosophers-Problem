/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:41:20 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/07 22:14:36 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(long long start_time)
{
	struct timeval	tmp;
	long long		curr_time;

	gettimeofday(&tmp, NULL);
	curr_time = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	return (curr_time - start_time);
}

void	my_print(const char *str, t_phl *philo)
{
	pthread_mutex_lock(&philo->gnrl->prnt);
	printf(str, get_time(philo->gnrl->start_time), philo->id);
	pthread_mutex_unlock(&philo->gnrl->prnt);
}

void	*action(void *phl)
{
	t_phl		*philo;
	long long	time_left;
	long long	totl_phl;

	philo = (t_phl *)phl;
	totl_phl = philo->gnrl->num_phil;
	if (philo->id % 2 == 0)
		usleep(philo->gnrl->tm_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(&philo->gnrl->forks[philo->id - 1]);
		my_print("%lld %lld has taken fork\n", philo);
		pthread_mutex_lock(&philo->gnrl->forks[philo->id % totl_phl]);
		my_print("%lld %lld has taken fork\n", philo);
		my_print("%lld %lld is eating\n", philo);
		usleep(philo->gnrl->tm_eat * 1000);
		pthread_mutex_unlock(&philo->gnrl->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->gnrl->forks[philo->id % totl_phl]);
		philo->last_meal = get_time(philo->gnrl->start_time);
		my_print("%lld %lld is sleeping\n", philo);
		usleep(philo->gnrl->tm_sleep * 1000);
		my_print("%lld %lld is thinking\n", philo);
	}
}

void	create_threads(t_gnrl *gnrl)
{
	long long		i;
	struct timeval	tm;

	i = 0;
	while (i < gnrl->num_phil)
		pthread_mutex_init(&gnrl->forks[i++], NULL);
	pthread_mutex_init(&gnrl->prnt, NULL);
	gettimeofday(&tm, NULL);
	gnrl->start_time = (tm.tv_usec / 1000) + (tm.tv_sec * 1000);
	i = 0;
	while (i < gnrl->num_phil)
	{
		gnrl->phls[i].last_meal = get_time(gnrl->start_time);
		pthread_create(&gnrl->phls[i].thread, NULL, &action, &gnrl->phls[i++]);
	}
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

// int main()

// {
// 	long long s ;
// 	printf("%lld\n", s);
// }