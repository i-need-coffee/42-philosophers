/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:20:33 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/12 16:59:53 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->print_lock);
	timestamp = get_time_ms() - philo->table->start_time;
	if (timestamp < 0)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return (false);
	}
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (true);
}
