/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:57:52 by obelaizi          #+#    #+#             */
/*   Updated: 2023/06/10 12:13:51 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_gnrl *gnrl)
{
	int		i;
	char	*tmp;

	i = -1;
	if (gnrl->nm_eat != -1)
	{
		i = 0;
		while (++i <= gnrl->num_phil)
		{
			tmp = ft_itoa(i);
			sem_wait(gnrl->phls[i - 1].num_eat);
			sem_unlink(tmp);
			free (tmp);
		}
		printf("enough is enough\n");
		kill(0, SIGINT);
	}
	waitpid(-1, NULL, 0);
	kill(0, SIGINT);
	sem_close(gnrl->forks);
	free(gnrl->phls);
	exit(0);
}
