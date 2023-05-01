/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:39:25 by obelaizi          #+#    #+#             */
/*   Updated: 2023/04/27 07:58:54 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct phl
{
	pthread_mutex_t	*forks;
	pthread_t		thread;
	int				id;
	long long		time_to_die;
}	t_phl;

typedef struct gnrl
{
	long long	num_phil;
	long long	tm_die;
	long long	tm_eat;
	long long	tm_sleep;
	long long	nm_eat;
	t_phl		*phls;
}	t_gnrl;

long long	ft_atoi(const char *str);

#endif