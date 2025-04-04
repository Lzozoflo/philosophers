/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:50:35 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/04 14:52:58 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief ft_unlock_mutex_fork that unlook the fork when a philo take
 * 			then before to end the sim.
 *
 */
int	ft_unlock_mutex_fork(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&p->l_fork);
		pthread_mutex_lock(p->r_fork);
	}
	else
	{
		pthread_mutex_lock(p->r_fork);
		pthread_mutex_lock(&p->l_fork);
	}
	*p->br_fork = 1;
	p->bl_fork = 1;
	if (p->id % 2 == 0)
	{
		pthread_mutex_unlock(&p->l_fork);
		pthread_mutex_unlock(p->r_fork);
	}
	else
	{
		pthread_mutex_unlock(p->r_fork);
		pthread_mutex_unlock(&p->l_fork);
	}
	return (1);
}

static void	ft_taken_fork(t_philo *p, pthread_mutex_t *m_fork, int *b_fork)
{
	time_t	timer;

	while (1)
	{
		pthread_mutex_lock(m_fork);
		if (*b_fork == AVAILABLE)
		{
			ft_status(p, FORK, &timer);
			*b_fork = UNAVAILABLE;
			pthread_mutex_unlock(m_fork);
			break ;
		}
		else
		{
			pthread_mutex_unlock(m_fork);
		}
	}
}

void	handle_fork(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		ft_taken_fork(p, &p->l_fork, &p->bl_fork);
		ft_taken_fork(p, p->r_fork, p->br_fork);
	}
	else
	{
		ft_taken_fork(p, p->r_fork, p->br_fork);
		ft_taken_fork(p, &p->l_fork, &p->bl_fork);
	}
}

