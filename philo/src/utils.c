/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:33:01 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/06 14:56:25 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	throw_error(char *err_msg, char *err_loc)
{
	write(2, "\033[31mERROR\033[0m ", 16);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, ": ", 2);
	write(2, err_loc, ft_strlen(err_loc));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

void	error_exit(char *err_msg, char *err_loc)
{
	throw_error(err_msg, err_loc);
	exit(EXIT_FAILURE);
}
