/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:09:33 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/31 11:12:07 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char *str);

void	parse_args(t_table *table, char **argv)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (argv[i])
	{
		if (!is_number(argv[i]))
		{
			throw_error("arg is not a number", argv[i]);
			error = 1;
		}
		i++;
	}
	if (error)
		exit(EXIT_FAILURE);
	printf("hello table, %d\n", table->must_eat_count);
}

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1])
		i++;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}
