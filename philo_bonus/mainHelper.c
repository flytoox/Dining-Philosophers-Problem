/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainHelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:13:03 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/23 19:21:29 by obelaizi         ###   ########.fr       */
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

void	*number_eat(void	*var)
{
	t_gnrl	*gnrl;
	int		i;
	int		total;

	gnrl = (t_gnrl *) var;
	while (1)
	{
		total = 0;
		i = -1;
		while (++i < gnrl->num_phil)
			if (gnrl->phls[i].nm_eat == 0)
				total++;
		sem_wait(gnrl->prnt);
		if (total == gnrl->num_phil)
		{
			sem_wait(gnrl->mu_dead);
			gnrl->dead = 0;
			sem_post(gnrl->mu_dead);
			return (printf("%d every philosopher ate enough\n",
					get_time(gnrl->start_time)), free_all(gnrl), NULL);
		}
		sem_post(gnrl->prnt);
	}
	return (NULL);
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
	while (time_now() - i <= time_sleep)
		usleep(200);
}
