/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diogenes_of_sinope.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:13:50 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/04 15:02:43 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

/**
 * @brief ft_diogenes_of_sinope
 */
void	*ft_diogenes_of_sinope(void *ptr_p)
{
	time_t	timer;
	t_philo	*p;
	int		count;

	p = ptr_p;
	count = 0;
	pthread_mutex_lock(&p->eat_lock);
	p->last_eat = p->start_time;
	pthread_mutex_unlock(&p->eat_lock);
	pthread_mutex_lock(&p->arg->start);
	pthread_mutex_unlock(&p->arg->start);
	ft_thinking(p);
	pthread_mutex_lock(&p->l_fork);
	ft_status(p, FORK, &timer);
	while (1)
	{
		if (ft_stop_sim(p))
		{
			pthread_mutex_unlock(&p->l_fork);
			return (0);
		}
	}
}
