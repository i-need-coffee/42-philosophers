/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:18:57 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/11 14:19:27 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long ms, t_table *table)
{
	long	start;
	long	now;

	start = get_time_ms();
	if (start < 0)
		return (stop_simulation(table));
	now = get_time_ms() - start;
	if (now < 0)
		return (stop_simulation(table));
	while (now < ms)
	{
		if (is_simulation_stopped(table))
			break ;
		usleep(500);
		now = get_time_ms() - start;
		if (now < 0)
			stop_simulation(table);
	}
}
