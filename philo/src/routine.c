/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 12:24:53 by shadya            #+#    #+#             */
/*   Updated: 2026/09/14 20:47:02 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	one_philo(t_philo *philo);
static bool	multiple_philos(t_philo *philo);
static bool	take_forks_and_eat(t_philo *philo,
				pthread_mutex_t *f1, pthread_mutex_t *f2);
static bool	eat_meal(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;
	int		took_fork;

	philo = (t_philo *)arg;
	took_fork = 0;
	while (is_simulation_stopped(philo->table) != true)
	{
		if (philo->table->nb_philo == 1)
		{
			if (!took_fork)
			{
				if (!one_philo(philo))
					return (stop_simulation(philo->table), NULL);
				took_fork = 1;
			}
		}
		else
		{
			if (!multiple_philos(philo))
				return (stop_simulation(philo->table), NULL);
		}
	}
	return (NULL);
}

static bool	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	pthread_mutex_unlock(philo->left_fork);
	return (true);
}

static bool	multiple_philos(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!take_forks_and_eat(philo, philo->left_fork, philo->right_fork))
			return (false);
	}
	else
	{
		if (!take_forks_and_eat(philo, philo->right_fork, philo->left_fork))
			return (false);
	}
	if (!print_status(philo, "is sleeping"))
		return (false);
	if (!ft_usleep(philo->table->time_to_sleep, philo->table))
		return (false);
	if (!print_status(philo, "is thinking"))
		return (false);
	return (true);
}

static bool	take_forks_and_eat(t_philo *philo,
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
