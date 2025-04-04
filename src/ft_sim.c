/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:13:50 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/02 13:36:46 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief ft_death_watchers are a monitor of the death.
 *
 */
static void	ft_death_watchers(t_data *data)
{
	unsigned int	i;
	unsigned int	j;

	i = data->arg.n_philo;
	ft_no_delay(data);
	j = 0;
	while (1)
	{
		if (ft_watch_time(&data->p[j], data))
			break ;
		if (++j == i)
			j = 0;
	}
	ft_pthread_join(data);
}

/**
 * @brief ft_routine are the routine of all philosopher
 * 			think eat sleep and repeats until one die
 *			or they reach the count of eating.
 */
static void	*ft_routine(void *ptr_p)
{
	t_philo	*p;
	int		count;

	p = ptr_p;
	count = 0;
	pthread_mutex_lock(&p->arg->start);
	pthread_mutex_unlock(&p->arg->start);
	if (ft_stop_sim(p))
		return (0);
	ft_thinking(p, get_time_in_ms());
	if (p->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (ft_get_fork(p, &count))
			return (0);
		if (ft_stop_sim(p))
			return (0);
	}
}

static void	ft_join_error(t_data *d, int nb_thread_created)
{
	int	i;

	i = 0;
	while (i < nb_thread_created)
	{
		pthread_join(d->p[i++].thread_id, NULL);
	}
}

static void	ft_one_fail(t_data *d, int i)
{
	pthread_mutex_lock(&d->arg.stop_sim);
	ft_stop_all(d);
	pthread_mutex_unlock(&d->arg.start);
	ft_join_error(d, i);
	free(d->p);
}

/**
 * @brief ft_start_sim init all thread to "ft_routine".
 */
int	ft_start_sim(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	pthread_mutex_lock(&d->arg.start);
	if (d->arg.n_philo == 1)
	{
		if (pthread_create(&d->p[i].thread_id, NULL, ft_diogenes_of_sinope,
				&d->p[0]))
			return (1);
		ft_death_watchers(d);
		return (0);
	}
	j = (int)d->arg.n_philo;
	while (i < j)
	{
		if (pthread_create(&d->p[i].thread_id, NULL, ft_routine, &d->p[i]))
		{
			ft_one_fail(d, i);
			return (1);
		}
		i++;
	}
	ft_death_watchers(d);
	return (0);
}
