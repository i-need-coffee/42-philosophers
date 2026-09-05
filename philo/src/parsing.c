/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:20:21 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/05 18:55:01 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	convert_str_to_lld(const char *nptr);
static bool			ft_isdigit(int c);
static void			set_table_args(t_table *table, char **argv);

bool	parse_args(t_table *table, char **argv)
{
	long long	value;
	int			error;
	int			i;

	error = 0;
	i = 0;
	while (argv[i])
	{
		value = convert_str_to_lld(argv[i]);
		if (i == 1 && (value > INT_MAX || value <= 0))
			error = throw_error(NB_PHILO, argv[i]);
		if (i == 5 && (value > INT_MAX || value < 0))
			error = throw_error(EAT_COUNT, argv[i]);
		if ((i > 1 && i < 5) && (value > LONG_MAX || value <= 0))
			error = throw_error(TIME_VALUE, argv[i]);
		i++;
	}
	if (error)
		return (false);
	set_table_args(table, argv);
	return (true);
}

static long long	convert_str_to_lld(const char *nptr)
{
	long long	res;
	long long	sign;
	long long	i;

	res = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (-1);
		if (res > (LLONG_MAX - (nptr[i] - '0')) / 10)
			return (-1);
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

static bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static void	set_table_args(t_table *table, char **argv)
{
	table->nb_philo = (int)convert_str_to_lld(argv[1]);
	table->time_to_die = (long)convert_str_to_lld(argv[2]);
	table->time_to_eat = (long)convert_str_to_lld(argv[3]);
	table->time_to_sleep = (long)convert_str_to_lld(argv[4]);
	if (argv[5])
		table->must_eat_count = (int)convert_str_to_lld(argv[5]);
}
