/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:39:25 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/22 19:10:28 by obelaizi         ###   ########.fr       */
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
	int				id;
	pthread_t		thread;
	pthread_mutex_t	mu_meal;
	int				last_meal;
	int				nm_eat;
	struct gnrl		*gnrl;
}	t_phl;

typedef struct gnrl
{
	int				dead;
	int				num_phil;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				nm_eat;
	int				start_time;
	pthread_mutex_t	*forks;
	t_phl			*phls;
	pthread_mutex_t	prnt;
	pthread_mutex_t	mu_dead;
}	t_gnrl;

int			ft_atoi(const char *str);
void		give_me_args(char **argv, int argc, t_gnrl *gnrl);
void		init_var(t_gnrl *gnrl);
void		check_death(t_gnrl *gnrl);
void		create_threads(t_gnrl *gnrl);
int			my_print(const char *str, t_phl *philo);
int			get_time(int start_time);
void		*number_eat(void	*var);
void		free_all(t_gnrl *gnrl);
void		ft_usleep(int time_sleep);
void		*action(void *phl);

#endif