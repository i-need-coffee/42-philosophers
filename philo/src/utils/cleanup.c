/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:16:19 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/12 14:59:10 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	cleanup(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->philos[i].last_meal_lock);
		pthread_mutex_destroy(&table->philos[i].meals_eaten_lock);
		i++;
	}
	free_and_null((void **)&table->philos);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free_and_null((void **)&table->forks);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->stop_lock);
}
