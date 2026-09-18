/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:43:14 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/18 12:07:29 by shadya           ###   ########.fr       */
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
		return (EXIT_FAILURE);
	if (!join_threads(&table))
		return (cleanup(&table, table.nb_philo), EXIT_FAILURE);
	cleanup(&table, table.nb_philo);
	return (EXIT_SUCCESS);
}
