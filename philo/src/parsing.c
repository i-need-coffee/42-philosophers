/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:09:33 by sjolliet          #+#    #+#             */
/*   Updated: 2026/03/31 16:47:45 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char *str);
static int	ft_isspace(int c);
static int	is_empty(char *str);
static long long	str_to_lld(char *str);
static void	init_table(t_table *table, char **argv);

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
		if (!str_to_lld(argv[i]))
		{
			throw_error("arg cannot be equal or inferior to 0", argv[i]);
			error = 1;
		}
		i++;
	}
	if (error)
		exit(EXIT_FAILURE);
	init_table(table, argv);
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

static long long str_to_lld(char *str)
{
	long long	res;
	long long	i;

	res = 0;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		return (0);
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

static void	init_table(t_table *table, char **argv)
{
	printf("test: %lld\n", str_to_lld(argv[1]));
	if (str_to_lld(argv[1]) > INT_MAX)
		error_exit("value must be an INT", argv[1]);
	if (ft_strlen(argv[2]) > 20 || str_to_lld(argv[2]) > LONG_MAX)
		error_exit("value must be a LONG", argv[2]);
	if (str_to_lld(argv[3]) > LONG_MAX)
		error_exit("value must be a LONG", argv[3]);
	if (str_to_lld(argv[4]) > LONG_MAX)
		error_exit("value must be a LONG", argv[4]);
	table->nb_philo = (int)str_to_lld(argv[1]);
	table->time_to_die = (long)str_to_lld(argv[2]);
	table->time_to_eat = (long)str_to_lld(argv[3]);
	table->time_to_sleep = (long)str_to_lld(argv[4]);
	if (argv[5])
	{
		if (str_to_lld(argv[5]) > INT_MAX)
			error_exit("value must be an INT", argv[5]);
		table->must_eat_count = (int)str_to_lld(argv[5]);
	}
	printf("nb philo: %d\n", table->nb_philo);
	printf("time_to_die: %ld\n", table->time_to_die);
	printf("time_to_eat: %ld\n", table->time_to_eat);
	printf("time_to_sleep: %ld\n", table->time_to_sleep);
	printf("must_eat_count: %d\n", table->must_eat_count);
}
