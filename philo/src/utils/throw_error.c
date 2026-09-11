/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 14:17:30 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/11 14:17:45 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	throw_error(char *err_msg, char *err_loc)
{
	write(2, "\033[31mERROR\033[0m ", 16);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, ": ", 2);
	write(2, err_loc, ft_strlen(err_loc));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}
