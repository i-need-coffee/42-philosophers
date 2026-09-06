/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 07:51:54 by shadya            #+#    #+#             */
/*   Updated: 2026/09/05 22:56:07 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *data);

bool	create_and_join_threads(t_table *table)
{
	pthread_t	philos[table->nb_philo];
	int			i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&philos[i], NULL, &routine, table) != 0)
			return (throw_error(strerror(errno), "pthread_create"), false);
		table->curr_philo++;
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(philos[i], NULL) != 0)
			return (throw_error(strerror(errno), "pthread_join"), false);
		i++;
	}
	return (true);
}

static void	*routine(void *data)
{
	t_table	*table;
	long	start;

	table = (t_table *)data;
	start = get_time_in_ms();
	while (1)
	{
		printf("%ld %d has taken a fork\n", (get_time_in_ms() - start), table->curr_philo);
		printf("%ld %d is eating\n", (get_time_in_ms() - start), table->curr_philo);
		ft_usleep(table->time_to_eat);
		printf("%ld %d is sleeping\n", (get_time_in_ms() - start), table->curr_philo);
		ft_usleep(table->time_to_sleep);
		printf("%ld %d is thinking\n", (get_time_in_ms() - start), table->curr_philo);
	}
	return (NULL);
}
