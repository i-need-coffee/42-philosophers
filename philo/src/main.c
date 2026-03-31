/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:43:14 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/31 10:09:26 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		throw_error("Program must have 4 or 5 args", "philo");
		return (1);
	}
	memset(&table, 0, sizeof(table));
	parse_args(&table, argv);
	return (0);
}
