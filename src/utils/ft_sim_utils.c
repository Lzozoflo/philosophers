/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sim_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:17:21 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/04 18:25:38 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <unistd.h>


/**
 * @brief ft_stop_sim check if the simulation need to stop.
 *
 */
int	ft_stop_sim(t_philo *p)
{
	pthread_mutex_lock(&p->arg->stop_sim);
	if (p->stop == STOP)
	{
		pthread_mutex_unlock(&p->arg->stop_sim);
		return (STOP);
	}
	pthread_mutex_unlock(&p->arg->stop_sim);
	return (START_CONTINUE);
}

/**
 * @brief ft_stop_all on the "normal death" stop all the sim
 * 			with "data->p[j].stop = STOP;".
 */
inline void	ft_stop_all(t_data *data)
{
	int	i;
	int	j;

	i = data->arg.n_philo;
	j = 0;
	while (1)
	{
		data->p[j].stop = STOP;
		if (++j == i)
			break ;
	}
	pthread_mutex_unlock(&data->arg.stop_sim);
}

/**
 * @brief ft_watch_time Check the time of death was not over
 *			and if its was because they stop on the count eat
 *			is not printing the death status is just waiting all stop.
 */
int	ft_watch_time(t_philo *p, t_data *data)
{
	time_t	timer;

	pthread_mutex_lock(&data->arg.stop_sim);
	if (p->arg->has_eat == p->arg->n_philo)
	{
		ft_stop_all(data);
		return (STOP);
	}
	pthread_mutex_unlock(&data->arg.stop_sim);
	pthread_mutex_lock(&data->arg.eat_lock);
	if (get_time_in_ms() - p->last_eat > data->arg.tt_die)
	{
		pthread_mutex_lock(&data->arg.stop_sim);
		pthread_mutex_unlock(&data->arg.eat_lock);
		ft_stop_all(data);
		usleep(1000);
		ft_status(p, DIED, &timer);
		return (STOP);
	}
	pthread_mutex_unlock(&data->arg.eat_lock);
	return (START_CONTINUE);
}

void	ft_pthread_join(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->arg.n_philo)
		pthread_join(d->p[i++].thread_id, NULL);
	ft_clear(d, 0);
}
