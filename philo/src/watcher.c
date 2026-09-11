/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:23:44 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/11 18:00:49 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watcher_routine(void *arg)
{
	t_table	*table;
	t_philo	*philos;
	int		i;
	long	last_meal;
	long	now;

	table = (t_table *)arg;
	philos = table->philos;
	while (1)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			now = get_time_ms();
			if (now < 0)
			{
				stop_simulation(table);
				break ;
			}
			pthread_mutex_lock(&philos->last_meal_lock);
			last_meal  = philos[i].last_meal;
			pthread_mutex_unlock(&philos->last_meal_lock);
			if ((now - last_meal) >= table->time_to_die)
			{
				print_status(&philos[i], "died");
				stop_simulation(table);
				break ;
			}
			i++;
		}
		if (is_simulation_stopped(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}


