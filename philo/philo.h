/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:39:25 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/07 22:15:54 by obelaizi         ###   ########.fr       */
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
	long long	id;
	pthread_t	thread;
	long long	last_meal;
	struct gnrl	*gnrl;
}	t_phl;

typedef struct gnrl
{
	long long		num_phil;
	long long		tm_die;
	long long		tm_eat;
	long long		tm_sleep;
	long long		nm_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	t_phl			*phls;
	pthread_mutex_t	prnt;
}	t_gnrl;

long long	ft_atoi(const char *str);
void		give_me_args(char **argv, int argc, t_gnrl *gnrl);
void		init_var(t_gnrl *gnrl);
void		check_death(t_gnrl *gnrl);
void		create_threads(t_gnrl *gnrl);
void		my_print(const char *str, t_phl *philo);
long long	get_time(long long start_time);

#endif