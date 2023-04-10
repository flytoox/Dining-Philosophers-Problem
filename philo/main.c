/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:41:20 by obelaizi          #+#    #+#             */
/*   Updated: 2023/04/07 03:14:55 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	*give_me_args(char **argv, int argc)
{
	long long	x;
	long long	*args;
	int			i;

	args = malloc(sizeof(long long) * (argc - 1));
	i = 0;
	while (i < argc - 1)
	{
		x = ft_atoi(*++argv);
		if (x == -1)
			return(printf("Dude don't enter something that not a number"), exit(1), NULL);
		args[i++] = x;
	}
	return (args);
}

// void	philo_5(t_gnrl gnrl)
// {

// }

// void	philo_6(t_gnrl gnrl)
// {

// }

// int	main(int argc, char **argv)
// {
// 	t_gnrl	gnrl;

// 	if (argc != 6 && argc != 5)
// 		return (printf("Dude Arguments is sus"), 1);
// 	gnrl.args = give_me_args(argv, argc);
// 	if (argc == 5)
// 		philo_5(gnrl);
// 	else	
// 		philo_6(gnrl);
// }

#include <pthread.h>
#include <stdio.h>

int shared_resource = 0;
pthread_mutex_t mutex;

void *thread_func(void *arg) {
    // acquire mutex
    pthread_mutex_lock(&mutex);
    // modify shared resource
    shared_resource++;
    // release mutex
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    // initialize mutex
    pthread_mutex_init(&mutex, NULL);
    // create threads
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_func, NULL);
    pthread_create(&thread2, NULL, thread_func, NULL);
    // wait for threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    // destroy mutex
    pthread_mutex_destroy(&mutex);
	sleep(1);
	printf("%d", shared_resource);
    return 0;
}
