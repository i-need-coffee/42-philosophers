/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:23:44 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/16 09:18:32 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	someone_died(t_philo *philo);
static bool	ate_all_meals(t_philo *philo);

void	*watcher_routine(void *arg)
{
	t_table	*table;
	int		i;
	int		philos_who_ate;

	table = (t_table *)arg;
	philos_who_ate = 0;
	while (is_simulation_stopped(table) != true)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (someone_died(&table->philos[i]))
				break ;
			if (table->must_eat_count && philos_who_ate == table->nb_philo)
			{
				stop_simulation(table);
				break ;
			}
			if (table->must_eat_count && ate_all_meals(&table->philos[i]))
				philos_who_ate++;
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

static bool	someone_died(t_philo *philo)
{
	long	last_meal;
	long	now;

	pthread_mutex_lock(&philo->last_meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
	now = get_time_ms();
	if (now < 0)
	{
		stop_simulation(philo->table);
		return (true);
	}
	if ((now - last_meal) > philo->table->time_to_die)
	{
		stop_simulation(philo->table);
		usleep(2000);
		print_status(philo, "died");
		return (true);
	}
	return (false);
}

static bool	ate_all_meals(t_philo *philo)
{
	int	meals_eaten;

	pthread_mutex_lock(&philo->meals_eaten_lock);
	meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
	if (meals_eaten < philo->table->must_eat_count)
		return (false);
	return (true);
}
