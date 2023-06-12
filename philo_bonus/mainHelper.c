/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainHelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:13:03 by obelaizi          #+#    #+#             */
/*   Updated: 2023/06/12 20:15:08 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		usleep(100);
}

int	count(int n)
{
	int	result;

	if (!n)
		return (1);
	result = 0;
	if (n < 0)
		result += 1;
	while (n != 0)
	{
		n /= 10;
		result++;
	}
	return (result);
}

void	create_semaphores(t_gnrl *gnrl)
{
	int		i;
	char	*tmp;

	i = 0;
	sem_unlink("/prnt");
	sem_unlink("/forks");
	// while (++i <= gnrl->num_phil)
	// {
	// 	tmp = ft_itoa(-i);
	// 	sem_unlink(tmp);
	// 	gnrl->phls[i - 1].mu_meal
	// 		= sem_open("/tmp", O_CREAT | O_EXCL, 0644, 1);
	// 	free(tmp);
	// }
	gnrl->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, gnrl->num_phil);
	gnrl->prnt = sem_open("/prnt", O_CREAT | O_EXCL, 0644, 1);
	i = -1;
	if (gnrl->nm_eat != -1)
	{	
		while (++i < gnrl->num_phil)
		{
			tmp = ft_itoa(i);
			sem_unlink(tmp);
			gnrl->phls[i].num_eat
				= sem_open(tmp, O_CREAT | O_EXCL, 0644, 0);
			free(tmp);
		}
	}
}
