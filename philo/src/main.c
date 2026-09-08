/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:43:14 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/08 14:22:11 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (throw_error(TOO_MANY_ARGS, "philo"));
	memset(&table, 0, sizeof(table));
	if (!parse_args(&table, argv))
		return (EXIT_FAILURE);
	if (!create_threads(&table))
	{
		cleanup(&table);
		return (EXIT_FAILURE);
	}
	cleanup(&table);
	return (EXIT_SUCCESS);
}
