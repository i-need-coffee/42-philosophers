/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 07:51:54 by shadya            #+#    #+#             */
/*   Updated: 2026/09/06 15:09:07 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_data(t_data *data);
static void	join_created_threads(pthread_t *threads, int created_count);

bool	create_threads(t_data *data)
{
	int	i;

	if (!init_data(data))
		return (false);
	i = 0;
	while (i < data->table.nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].table = &data->table;
		if (pthread_create(&data->threads[i], NULL,
				&routine, &data->philos[i]) != 0)
		{
			throw_error(strerror(errno), "pthread_create");
			join_created_threads(data->threads, i);
			return (false);
		}
		i++;
	}
	join_created_threads(data->threads, data->table.nb_philo);
	return (true);
}

static bool	init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->table.nb_philo);
	if (!data->philos)
		return (throw_error(ERR_ALLOC, "init_data"), false);
	data->threads = malloc(sizeof(pthread_t) * data->table.nb_philo);
	if (!data->threads)
		return (throw_error(ERR_ALLOC, "init_data"), false);
	return (true);
}

static void	join_created_threads(pthread_t *threads, int created_count)
{
	int	i;

	i = 0;
	while (i < created_count)
	{
		if (pthread_join(threads[i], NULL) != 0)
			throw_error(strerror(errno), "pthread_join");
		i++;
	}
}
