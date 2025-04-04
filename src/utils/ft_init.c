/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:50:34 by fcretin           #+#    #+#             */
/*   Updated: 2025/03/30 16:50:34 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

/**
 * @brief ft_mutex_init_arg init the t_arg mutex.
 *
 */
static int	ft_mutex_init_arg(t_arg *arg)
{
	if (pthread_mutex_init(&arg->start, NULL))
		return (1);
	if (pthread_mutex_init(&arg->stop_sim, NULL))
		return (1);
	if (pthread_mutex_init(&arg->write_lock, NULL))
		return (1);
	return (0);
}

/**
 * @brief ft_mutex_init init the t_philo mutex.
 *
 */
static int	ft_mutex_init_p(t_philo *p)
{
	p->r_fork = NULL;
	if (pthread_mutex_init(&p->eat_lock, NULL))
		return (1);
	if (pthread_mutex_init(&p->l_fork, NULL))
		return (1);
	p->stop = START_CONTINUE;
	return (0);
}

/**
 * @brief ft_get_arg copy all data so all philo know they time to die
 *		sleep and more.
 *
 */
static void	ft_get_arg(t_arg *arg, t_philo *p)
{
	p->arg = arg;
	p->bl_fork = 1;
	p->tt_eat = arg->tt_eat;
	p->tt_die = arg->tt_die;
	p->tt_sleep = arg->tt_sleep;
	p->start_time = arg->start_time;
	p->eat_count = arg->eat_count;
	p->last_eat = p->start_time;
}

/**
 * @brief initializes all the philosophers their values and the mutexes.
 *
 */
int	ft_init(t_arg *arg, t_philo *p)
{
	unsigned int	i;

	i = 0;
	if (ft_mutex_init_arg(arg))
		return (1);
	arg->start_time = get_time_in_ms() + (arg->n_philo * 10);
	while (i < arg->n_philo)
	{
		p[i].id = i + 1;
		ft_get_arg(arg, &p[i]);
		if (ft_mutex_init_p(&p[i]))
			return (1);
		if (i == arg->n_philo - 1)
		{
			p[i].br_fork = &p[0].bl_fork;
			p[i].r_fork = &p[0].l_fork;
		}
		else
		{
			p[i].br_fork = &p[i + 1].bl_fork;
			p[i].r_fork = &p[i + 1].l_fork;
		}
		i++;
	}
	return (0);
}
