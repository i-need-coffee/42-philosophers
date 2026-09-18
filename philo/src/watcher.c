/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:23:44 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/18 12:51:47 by shadya           ###   ########.fr       */
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
	while (is_simulation_stopped(table) != true)
	{
		i = 0;
		philos_who_ate = 0;
		while (i < table->nb_philo)
		{
			if (someone_died(&table->philos[i]))
				return (NULL);
			if (table->must_eat_count && ate_all_meals(&table->philos[i]))
				philos_who_ate++;
			i++;
		}
		if (table->must_eat_count && philos_who_ate == table->nb_philo)
		{
			stop_simulation(table);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

bool	check_death(t_philo *philo, long now)
{
	if (now - philo->last_meal < philo->table->time_to_die)
		return (false);
	pthread_mutex_lock(&philo->table->print_lock);
	if (!is_simulation_stopped(philo->table))
	{
		stop_simulation(philo->table);
		printf("%ld %d died\n", now - philo->table->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
	return (true);
}

static bool	someone_died(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->last_meal_lock);
	now = get_time_ms();
	if (now < 0)
	{
		pthread_mutex_unlock(&philo->last_meal_lock);
		stop_simulation(philo->table);
		return (true);
	}
	if (check_death(philo, now))
	{
		pthread_mutex_unlock(&philo->last_meal_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->last_meal_lock);
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
