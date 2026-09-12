/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:18:57 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/12 17:36:14 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_usleep(long ms, t_table *table)
{
	long	start;
	long	now;

	start = get_time_ms();
	if (start < 0)
		return (false);
	now = get_time_ms() - start;
	if (now < 0)
		return (false);
	while (now < ms && !is_simulation_stopped(table))
	{
		usleep(500);
		now = get_time_ms() - start;
		if (now < 0)
			return (false);
	}
	return (true);
}
