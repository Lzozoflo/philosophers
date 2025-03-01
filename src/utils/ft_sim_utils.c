/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sim_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:17:21 by fcretin           #+#    #+#             */
/*   Updated: 2025/02/28 13:15:35 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

/**
 * @brief ft_stop_sim check if the simulation need to stop.
 *
 */
inline int	ft_stop_sim(t_philo *p)
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
	unsigned int	i;
	unsigned int	j;

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
 * @brief ft_all_end_count_eat Check if all philo finish to eat.
 *
 */
static inline int	ft_is_all_eat_stop(t_data *data)
{
	unsigned int	j;
	unsigned int	i;

	i = data->arg.n_philo;
	j = 0;
	while (1)
	{
		if (data->p[j].stop != EAT_STOP)
		{
			pthread_mutex_unlock(&data->arg.stop_sim);
			return (START_CONTINUE);
		}
		if (++j == i)
			break ;
	}
	ft_stop_all(data);
	return (STOP);
}

/**
 * @brief ft_watch_time Check the time of death was not over
 *			and if its was because they stop on the count eat
 *			is not printing the death status is just waiting all stop.
 */
int	ft_watch_time(t_philo *p, t_data *data)
{
	pthread_mutex_lock(&data->arg.stop_sim);
	if (p->stop == EAT_STOP)
	{
		if (ft_is_all_eat_stop(data) == STOP)
			return (STOP);
		return (START_CONTINUE);
	}
	pthread_mutex_unlock(&data->arg.stop_sim);
	pthread_mutex_lock(&p->eat_lock);
	if (get_time_in_ms() - p->last_eat > data->arg.tt_die)
	{
		pthread_mutex_lock(&data->arg.stop_sim);
		pthread_mutex_unlock(&p->eat_lock);
		ft_stop_all(data);
		ft_usleep(get_time_in_ms(), 1);
		ft_status(p, DIED, get_time_in_ms());
		return (STOP);
	}
	pthread_mutex_unlock(&p->eat_lock);
	return (START_CONTINUE);
}

void	ft_pthread_join(t_data *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->arg.n_philo)
	{
		pthread_join(d->p[i++].thread_id, NULL);
	}
	ft_clear(d, 1);
}
