/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:17:02 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/07 08:07:41 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <stdlib.h>

void	ft_mutex_destroy_arg(t_arg *arg, int nb)
{
	if (nb >= 1)
		pthread_mutex_destroy(&arg->start);
	if (nb >= 2)
		pthread_mutex_destroy(&arg->stop_sim);
	if (nb >= 3)
		pthread_mutex_destroy(&arg->write_lock);
	if (nb >= 4)
		pthread_mutex_destroy(&arg->eat_lock);
}

int	ft_clear(t_data *data, int nb)
{
	int	i;

	if (nb)
		i = nb;
	else
		i = data->arg.n_philo;
	while (--i != -1)
		pthread_mutex_destroy(&data->p[i].l_fork);
		// pthread_mutex_destroy(&data->p[i].eat_lock);
	}
	pthread_mutex_destroy(&data->arg.eat_lock);
	pthread_mutex_destroy(&data->arg.write_lock);
	pthread_mutex_destroy(&data->arg.stop_sim);
	pthread_mutex_destroy(&data->arg.start);
	free(data->p);
	return (1);
}
