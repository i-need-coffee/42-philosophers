/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:43:14 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/06 15:00:14 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (throw_error(TOO_MANY_ARGS, "philo"));
	memset(&data, 0, sizeof(data));
	if (!parse_args(&data.table, argv))
		return (EXIT_FAILURE);
	if (!create_threads(&data))
	{
		cleanup(&data);
		return (EXIT_FAILURE);
	}
	cleanup(&data);
	return (EXIT_SUCCESS);
}
