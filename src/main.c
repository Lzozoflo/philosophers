/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:45:14 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/04 17:08:55 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <unistd.h>
#include <stdlib.h>

static int	ft_print_param(void)
{
	write(2, "Wrong/no arg...\n", 16);
	write(2, "arg1 = number of philosophers\narg2 = time_to_die\n", 49);
	write(2, "arg3 = time_to_eat\narg4 = time_to_sleep\narg5(optional)", 54);
	write(2, " = number_of_times_each_philosopher_must_eat\n", 45);
	return (2);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.p = NULL;
	if (ft_param(ac, av, &data.arg))
		return (ft_print_param());
	data.p = malloc(sizeof(t_philo) * (size_t)data.arg.n_philo);
	if (!data.p)
		return (1);
	if (ft_init(&data.arg, data.p, &data))
		return (1);
	if (ft_start_sim(&data))
		return (1);
	return (0);
}
