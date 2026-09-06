/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:33:01 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/06 14:55:25 by shadya           ###   ########.fr       */
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

void	free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	free_and_null((void **)&data->philos);
	free_and_null((void **)&data->threads);
}
