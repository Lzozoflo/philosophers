/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:13:24 by fcretin           #+#    #+#             */
/*   Updated: 2025/03/19 15:45:46 by fcretin          ###   ########.fr       */
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
inline void	ft_thinking(t_philo *p, time_t timer)
{
	ft_status(p, THINKING, timer);
	usleep(500);
	if (p->tt_eat > p->tt_sleep)
		ft_usleep(p->start_time, p->tt_eat - p->tt_sleep);
}

/**
 * @brief ft_sleep_time usleep to X ms (from tt_sleep)
 *		and print the status to simulate a philosophe sleeping.
 */
static void	ft_sleeping(t_philo *p, time_t timer)
{
	ft_status(p, SLEEPING, timer);
	if (ft_stop_sim(p))
		return ;
	ft_usleep(timer, p->tt_sleep);
	ft_thinking(p, get_time_in_ms());
}

/**
 * @brief ft_unlock_mutex_fork that unlook the fork when a philo take
 * 			then before to end the sim.
 *
 */
static int	ft_unlock_mutex_fork(t_philo *p)
{
	pthread_mutex_unlock(&p->l_fork);
	pthread_mutex_unlock(p->r_fork);
	return (1);
}

/**
 * @brief ft_check_count chech the count to stop the sim
 *
 */
static inline int	ft_check_count(t_philo *p, int *count)
{
	if (p->eat_count == NO_COUNT)
		return (START_CONTINUE);
	if (++(*count) == p->eat_count)
	{
		pthread_mutex_lock(&p->arg->stop_sim);
		p->stop = EAT_STOP;
		pthread_mutex_unlock(&p->arg->stop_sim);
		return (STOP);
	}
	return (START_CONTINUE);
}

int	ft_get_fork(t_philo *p, int *count)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	time_t			timer;

	first = p->r_fork;
	second = &p->l_fork;
	pthread_mutex_lock(first);
	ft_status(p, FORK, get_time_in_ms());
	pthread_mutex_lock(second);
	ft_status(p, FORK, get_time_in_ms());
	if (ft_stop_sim(p) == STOP)
		return (ft_unlock_mutex_fork(p));
	timer = get_time_in_ms();
	ft_status(p, EATING, timer);
	ft_usleep(timer, p->tt_eat);
	ft_check_count(p, count);
	if (ft_stop_sim(p) == STOP)
		return (ft_unlock_mutex_fork(p));
	ft_unlock_mutex_fork(p);
	ft_sleeping(p, get_time_in_ms());
	return (0);
}
