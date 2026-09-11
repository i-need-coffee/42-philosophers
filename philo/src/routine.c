/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 12:24:53 by shadya            #+#    #+#             */
/*   Updated: 2026/09/11 18:10:00 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo_routine(t_philo *philo);
static void	take_forks_and_eat(t_philo *philo);
static void	eat_meal(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	int		took_fork;

	philo = (t_philo *)arg;
	table = philo->table;
	took_fork = 0;
	while (1)
	{
		if (is_simulation_stopped(table))
			break ;
		if (table->nb_philo == 1)
		{
			if (!took_fork)
				one_philo_routine(philo);
			took_fork = 1;
		}
		else
		{
			take_forks_and_eat(philo);
			if (is_simulation_stopped(table))
				break ;
			print_status(philo, "is sleeping");
			ft_usleep(table->time_to_sleep, table);
			if (is_simulation_stopped(table))
				break ;
			print_status(philo, "is thinking");
		}
	}
	return (NULL);
}

static void	one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
}

static void	take_forks_and_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		eat_meal(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		eat_meal(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

static void	eat_meal(t_philo *philo)
{
	long	timestamp;

	timestamp = get_time_ms();
	if (timestamp < 0)
	{
		stop_simulation(philo->table);
		return ;
	}
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = timestamp;
	pthread_mutex_unlock(&philo->last_meal_lock);
	print_status(philo, "is eating");
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->meals_eaten_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
}
