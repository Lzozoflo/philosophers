/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:03:36 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/02 15:18:34 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

/**
 * @brief ft_unlock_mutex_fork that unlook the fork when a philo take
 * 			then before to end the sim.
 *
 */
int	ft_unlock_mutex_fork(t_philo *p)
{
	*p->br_fork = 1;
	p->bl_fork = 1;
	if (p->id % 2 == 0)
	{
		pthread_mutex_unlock(p->r_fork);
		pthread_mutex_unlock(&p->l_fork);
	}
	else
	{
		pthread_mutex_unlock(&p->l_fork);
		pthread_mutex_unlock(p->r_fork);
	}
	return (1);
}

int	handle_fork_0(t_philo *p)
{
	pthread_mutex_lock(p->r_fork);
	if (*p->br_fork == 1)
	{
		ft_status(p, FORK, get_time_in_ms());
		*p->br_fork = 0;
	}
	else
	{
		pthread_mutex_unlock(p->r_fork);
		return (1);
	}
	pthread_mutex_lock(&p->l_fork);
	if (p->bl_fork == 1)
	{
		ft_status(p, FORK, get_time_in_ms());
		p->bl_fork = 0;
	}
	else
	{
		ft_unlock_mutex_fork(p);
		return (1);
	}
	return (0);
}

int	handle_fork_1(t_philo *p)
{
	pthread_mutex_lock(&p->l_fork);
	if (p->bl_fork == 1)
	{
		ft_status(p, FORK, get_time_in_ms());
		p->bl_fork = 0;
	}
	else
	{
		pthread_mutex_unlock(&p->l_fork);
		return (1);
	}
	pthread_mutex_lock(p->r_fork);
	if (*p->br_fork == 1)
	{
		ft_status(p, FORK, get_time_in_ms());
		*p->br_fork = 0;
	}
	else
	{
		ft_unlock_mutex_fork(p);
		return (1);
	}
	return (0);
}

int	handle_fork(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		return (handle_fork_0(p));
	}
	else
	{
		return (handle_fork_1(p));
	}
}
