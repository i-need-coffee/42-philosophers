/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:20:33 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/18 11:20:24 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_status(t_philo *philo, char *status)
{
	long	now;

	pthread_mutex_lock(&philo->table->print_lock);
	if (is_simulation_stopped(philo->table))
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return (false);
	}
	now = get_time_ms();
	if (now < 0)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return (false);
	}
	printf("%ld %d %s\n",
		now - philo->table->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (true);
}
