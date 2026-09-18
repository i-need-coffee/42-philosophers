/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 12:20:18 by shadya            #+#    #+#             */
/*   Updated: 2026/09/18 12:43:51 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	eat_meal(t_philo *philo);

bool	take_forks_and_eat(t_philo *philo,
				pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	pthread_mutex_lock(f1);
	if (!print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(f1);
		return (false);
	}
	pthread_mutex_lock(f2);
	if (!print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(f1);
		pthread_mutex_unlock(f2);
		return (false);
	}
	if (!eat_meal(philo))
	{
		pthread_mutex_unlock(f1);
		pthread_mutex_unlock(f2);
		return (false);
	}
	pthread_mutex_unlock(f1);
	pthread_mutex_unlock(f2);
	return (true);
}

bool	think(t_philo *philo)
{
	long	time_to_think;

	if (!print_status(philo, "is thinking"))
		return (false);
	time_to_think = 0;
	if (philo->table->nb_philo % 2 != 0)
		time_to_think = (2 * philo->table->time_to_eat
				- philo->table->time_to_sleep) / 2;
	if (time_to_think > 0)
	{
		if (!ft_usleep(time_to_think, philo->table))
			return (false);
	}
	return (true);
}

static bool	eat_meal(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->last_meal_lock);
	timestamp = get_time_ms();
	if (timestamp < 0)
	{
		pthread_mutex_unlock(&philo->last_meal_lock);
		return (false);
	}
	philo->last_meal = timestamp;
	pthread_mutex_unlock(&philo->last_meal_lock);
	if (!print_status(philo, "is eating"))
		return (false);
	if (!ft_usleep(philo->table->time_to_eat, philo->table))
		return (false);
	pthread_mutex_lock(&philo->meals_eaten_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
	return (true);
}
