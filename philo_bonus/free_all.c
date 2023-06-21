/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:57:52 by obelaizi          #+#    #+#             */
/*   Updated: 2023/06/21 12:26:02 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_helper(t_gnrl *gnrl)
{
	sem_close(gnrl->forks);
	sem_close(gnrl->prnt);
	sem_unlink("/prnt");
	sem_unlink("/forks");
	free(gnrl->phls);
	kill(0, SIGINT);
}

void	*check_nm_eat(void *var)
{
	t_gnrl	*gnrl;
	int		i;
	char	*tmp;

	gnrl = (t_gnrl *)var;
	i = 0;
	while (++i <= gnrl->num_phil)
	{
		tmp = ft_itoa(i);
		sem_wait(gnrl->phls[i - 1].num_eat);
		sem_unlink(tmp);
		free (tmp);
	}
	sem_wait(gnrl->prnt);
	printf("Enough is enough\n");
	free_helper(gnrl);
	return (NULL);
}

void	free_all(t_gnrl *gnrl)
{
	if (!gnrl->nm_eat)
	{
		sem_wait(gnrl->prnt);
		printf("Enough is enough\n");
		free_helper(gnrl);
	}
	if (gnrl->nm_eat != -1)
	{
		pthread_create(&gnrl->thr_nm_eat, NULL, &check_nm_eat, gnrl);
		pthread_detach(gnrl->thr_nm_eat);
	}
	waitpid(-1, NULL, 0);
	free_helper(gnrl);
}
