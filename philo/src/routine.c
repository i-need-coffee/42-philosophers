/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 12:24:53 by shadya            #+#    #+#             */
/*   Updated: 2026/09/10 18:44:35 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_simulation(t_table *table);
static void	eat_meal(t_philo *philo, t_table *table);
static bool	print_status(t_philo *philo, char *status);

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (table->simulation_stop != true)
	{
		eat_meal(philo, table);
		print_status(philo, "is eating");
		usleep(table->time_to_eat * 1000);
		print_status(philo, "is sleeping");
		usleep(table->time_to_sleep * 1000);
		stop_simulation(table);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

static void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->stop_lock);
	table->simulation_stop = true;
	pthread_mutex_unlock(&table->stop_lock);
}

static void	eat_meal(t_philo *philo, t_table *table)
{
	if (table->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		usleep(table->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		usleep(table->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

static bool	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	timestamp = get_time_ms() - philo->table->start_time;
	if (timestamp < 0)
		return (false);
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (true);
}
