/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:39:25 by obelaizi          #+#    #+#             */
/*   Updated: 2023/06/10 12:19:59 by obelaizi         ###   ########.fr       */
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
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>

typedef struct phl
{
	int				id;
	pthread_t		thread;
	sem_t			*mu_meal;
	sem_t			*num_eat;
	int				last_meal;
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
	sem_t			*forks;
	t_phl			*phls;
	sem_t			*prnt;
	sem_t			*mu_dead;
}	t_gnrl;

int			ft_atoi(const char *str);
void		give_me_args(char **argv, int argc, t_gnrl *gnrl);
void		init_var(t_gnrl *gnrl);
void		*check_death(void *phl);
void		create_threads(t_gnrl *gnrl);
int			my_print(const char *str, t_phl *philo);
int			get_time(int start_time);
void		free_all(t_gnrl *gnrl);
void		ft_usleep(int time_sleep);
void		*action(void *phl);
int			count(int n);
char		*ft_itoa(int n);
void		create_semaphores(t_gnrl *gnrl);
int			time_now(void);

#endif