/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:17:02 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/04 16:30:06 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <stdlib.h>

/**
 * @brief Not realy
 */
int	ft_clear(t_data *data, int return_v)
{
	int	i;

	i = (int)data->arg.n_philo;
	while (--i != -1)
		pthread_mutex_destroy(&data->p[i].l_fork);
	pthread_mutex_destroy(&data->arg.eat_lock);
	pthread_mutex_destroy(&data->arg.write_lock);
	pthread_mutex_destroy(&data->arg.stop_sim);
	pthread_mutex_destroy(&data->arg.start);
	free(data->p);
	return (return_v);
}
