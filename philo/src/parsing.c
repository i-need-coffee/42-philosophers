/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:09:33 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/31 11:45:53 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char *str);
static int	ft_isspace(int c);
static int	is_empty(char *str);

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

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	is_empty(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_number(char *str)
{
	int	i;

	if (is_empty(str))
		return (0);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1])
		i++;
	while (str[i])
	{
		if ((str[i] < 48 || str[i] > 57) && !ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

