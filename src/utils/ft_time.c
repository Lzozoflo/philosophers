/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:01:38 by fcretin           #+#    #+#             */
/*   Updated: 2025/02/27 16:36:49 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <sys/time.h>
#include <unistd.h>

/**
 * @brief Get the time in ms object
 */
inline time_t	get_time_in_ms(void)
{
	struct timeval		time_struct;

	gettimeofday(&time_struct, NULL);
	return (((time_struct.tv_sec * 1000) + (time_struct.tv_usec / 1000)));
}

/**
 * @brief Delays the launch to synchronize all threads at start_time.
 *
 */
inline void	ft_no_delay(t_data *data)
{
	time_t	start_time;

	start_time = data->arg.start_time;
	while (get_time_in_ms() < start_time)
		continue ;
	pthread_mutex_unlock(&data->arg.start);
}

void	ft_usleep(time_t time, __useconds_t tt_some)
{
	time += tt_some;
	while (get_time_in_ms() < time)
		usleep(100);
}
