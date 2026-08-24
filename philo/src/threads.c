/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 07:51:54 by shadya            #+#    #+#             */
/*   Updated: 2026/08/24 08:36:47 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int	i;

	i = *(int *)arg;
	i++;
	sleep(2);
	printf("Current philo: %d\n", i);
	return ((void *)arg);
}

void	create_and_join_threads(t_table *table)
{
	pthread_t	th[table->nb_philo];
	int			i;
	int			*philo;

	i = 0;
	while (i < table->nb_philo)
	{
		philo = malloc(sizeof(int));
		if (!philo)
			error_exit(ERR_ALLOC, "create thread");
		*philo = i;
		if (pthread_create(&th[i], NULL, &routine, philo) != 0)
			error_exit(strerror(errno), "create thread");
		free_and_null((void **)&philo);
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(th[i], NULL) != 0)
			error_exit(strerror(errno), "join thread");
		i++;
	}
}
