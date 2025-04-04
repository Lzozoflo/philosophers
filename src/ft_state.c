/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:13:24 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/04 17:45:33 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief ft_thinking is the state of thinking what forks takes
 *		and print the status to simulate a philosophe thinking.
 *		th
 */
inline void	ft_first_thinking(t_philo *p)
{
	time_t	timer;

	ft_status(p, THINKING, &timer);
}

/**
 * @brief ft_thinking is the state of thinking what forks takes
 *		and print the status to simulate a philosophe thinking.
 *		th
 */
inline void	ft_thinking(t_philo *p)
{
	time_t	timer;

	ft_status(p, THINKING, &timer);
	usleep(200);
	if (p->arg->n_philo % 2 != 0)
		ft_usleep(timer, p->tt_eat);
}

/**
 * @brief print the status and simulate a philosophe sleeping.
 */
inline void	ft_sleeping(t_philo *p)
{
	time_t	timer;

	ft_status(p, SLEEPING, &timer);
	if (ft_stop_sim(p))
		return ;
	ft_usleep(timer, p->tt_sleep);
}

/**
 * @brief ft_check_count chech the count to stop the sim
 *
 */
static inline void	ft_check_count(t_philo *p, int *count)
{
	if (p->eat_count == NO_COUNT)
		return ;
	if (++(*count) == p->eat_count)
	{
		pthread_mutex_lock(&p->arg->stop_sim);
		p->arg->has_eat++;
		pthread_mutex_unlock(&p->arg->stop_sim);
	}
}

int	ft_get_fork(t_philo *p, int *count)
{
	time_t	timer;

	handle_fork(p);
	if (ft_stop_sim(p) == STOP)
		return (ft_unlock_mutex_fork(p));
	ft_status(p, EATING, &timer);
	ft_usleep(timer, p->tt_eat);
	ft_check_count(p, count);
	if (ft_stop_sim(p) == STOP)
		return (ft_unlock_mutex_fork(p));
	ft_unlock_mutex_fork(p);
	return (0);
}
