/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainHelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:13:03 by obelaizi          #+#    #+#             */
/*   Updated: 2023/06/21 12:06:02 by obelaizi         ###   ########.fr       */
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

int	number_eat_helper(t_gnrl *gnrl, int *total)
{
	int	i;

	i = -1;
	while (++i < gnrl->num_phil)
	{
		pthread_mutex_lock(&gnrl->phls[i].mu_nm_eat);
		if (gnrl->phls[i].nm_eat == 0)
			(*total)++;
		pthread_mutex_unlock(&gnrl->phls[i].mu_nm_eat);
	}
	pthread_mutex_lock(&gnrl->prnt);
	if (*total == gnrl->num_phil)
	{
		pthread_mutex_lock(&gnrl->mu_dead);
		if (!gnrl->dead)
			return (pthread_mutex_unlock(&gnrl->mu_dead),
				pthread_mutex_unlock(&gnrl->prnt), 1);
		gnrl->dead = 0;
		pthread_mutex_unlock(&gnrl->mu_dead);
		return (printf("%d Enough is Enough\n", get_time(gnrl->start_time)),
			pthread_mutex_unlock(&gnrl->prnt), 1);
	}
	pthread_mutex_unlock(&gnrl->prnt);
	return (0);
}

void	*number_eat(void	*var)
{
	t_gnrl	*gnrl;
	int		total;

	gnrl = (t_gnrl *) var;
	while (1)
	{
		pthread_mutex_lock(&gnrl->mu_dead);
		if (!gnrl->dead)
			return (pthread_mutex_unlock(&gnrl->mu_dead), NULL);
		pthread_mutex_unlock(&gnrl->mu_dead);
		total = 0;
		if (number_eat_helper(gnrl, &total))
			return (NULL);
		usleep(200);
	}
}

int	time_now(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return ((tm.tv_usec / 1000) + (tm.tv_sec * 1000));
}

void	ft_usleep(int time_sleep)
{
	int	i;

	i = time_now();
	while (time_now() - i < time_sleep)
		usleep(50);
}
