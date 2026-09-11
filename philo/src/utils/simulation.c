/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:25:44 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/11 14:26:15 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulation_stopped(t_table *table)
{
	bool	has_stopped;

	pthread_mutex_lock(&table->stop_lock);
	has_stopped = table->simulation_stop;
	pthread_mutex_unlock(&table->stop_lock);
	return (has_stopped);
}

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->stop_lock);
	table->simulation_stop = true;
	pthread_mutex_unlock(&table->stop_lock);
}
