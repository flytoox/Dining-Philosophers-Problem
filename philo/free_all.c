/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:57:52 by obelaizi          #+#    #+#             */
/*   Updated: 2023/05/10 18:01:11 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_gnrl *gnrl)
{
	int	i;

	i = 0;
	while (i < gnrl->num_phil)
	{
		pthread_join(gnrl->phls[i].thread, NULL);
		// pthread_mutex_unlock(&gnrl->forks[i]);
		// pthread_mutex_destroy(&gnrl->forks[i]);
		// pthread_detach(gnrl->phls[i].thread);
		i++;
	}
	// pthread_mutex_unlock(&gnrl->prnt);
	// pthread_mutex_destroy(&gnrl->prnt);
	free(gnrl->forks);
	// free(gnrl->phls);
	// pthread_mutex_unlock(&gnrl->prnt);
	exit(0);
}
