/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:57:52 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/22 19:15:54 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_gnrl *gnrl)
{
	int	i;

	i = -1;
	while (++i < gnrl->num_phil)
		pthread_join(gnrl->phls[i].thread, NULL);
	i = -1;
	while (++i < gnrl->num_phil)
	{
		pthread_mutex_destroy(&gnrl->phls[i].mu_meal);
		pthread_mutex_destroy(&gnrl->forks[i]);
	}
	pthread_mutex_destroy(&gnrl->prnt);
	pthread_mutex_destroy(&gnrl->mu_dead);
	free(gnrl->forks);
	free(gnrl->phls);
	exit(0);
}
