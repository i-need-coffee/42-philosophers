/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:16:19 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/18 12:02:33 by shadya           ###   ########.fr       */
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

void	cleanup(t_table *table, int created_count)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (i < created_count)
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
