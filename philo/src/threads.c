/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 07:51:54 by shadya            #+#    #+#             */
/*   Updated: 2026/09/18 12:19:08 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_table(t_table *table);
static void	init_philo(t_table *table, int i);
static bool	join_created_threads(t_philo *philos, int created_count);

bool	create_threads(t_table *table)
{
	int	i;

	if (!init_table(table))
		return (false);
	i = 0;
	while (i < table->nb_philo)
	{
		init_philo(table, i);
		if (pthread_create(&table->philos[i].thread, NULL,
				&routine, &table->philos[i]) != 0)
			return (throw_error(THREAD_CREATE, "pthread_create"),
				stop_simulation(table),
				join_created_threads(table->philos, i),
				cleanup(table, i), false);
		i++;
	}
	if (pthread_create(&table->watcher, NULL, &watcher_routine, table) != 0)
		return (throw_error(THREAD_CREATE, "pthread_create"),
			stop_simulation(table), join_created_threads(table->philos,
				table->nb_philo), cleanup(table, table->nb_philo), false);
	return (true);
}

bool	join_threads(t_table *table)
{
	int	error;

	error = 0;
	if (!join_created_threads(table->philos, table->nb_philo))
		error = 1;
	if (pthread_join(table->watcher, NULL) != 0)
	{
		throw_error(THREAD_JOIN, "pthread_join");
		error = 1;
	}
	if (error)
		return (false);
	return (true);
}

static bool	init_table(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (throw_error(ERR_ALLOC, "init_table"), false);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		return (free(table->philos),
			throw_error(ERR_ALLOC, "init_table"), false);
	table->start_time = get_time_ms();
	if (table->start_time == -1)
		return (free(table->philos), free(table->forks), false);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->stop_lock, NULL);
	return (true);
}

static void	init_philo(t_table *table, int i)
{
	table->philos[i].id = i + 1;
	table->philos[i].table = table;
	table->philos[i].left_fork = &table->forks[i];
	table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
	table->philos[i].last_meal = table->start_time;
	table->philos[i].meals_eaten = 0;
	pthread_mutex_init(&table->philos[i].last_meal_lock, NULL);
	pthread_mutex_init(&table->philos[i].meals_eaten_lock, NULL);
}

static bool	join_created_threads(t_philo *philos, int created_count)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	while (i < created_count)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			throw_error(THREAD_JOIN, "pthread_join");
			error = 1;
		}
		i++;
	}
	if (error)
		return (false);
	return (true);
}
