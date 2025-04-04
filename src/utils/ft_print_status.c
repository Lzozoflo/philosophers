/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:29:18 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/04 18:16:18 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <stdio.h>

/**
 * @brief ft_put_status everytime a philosopher do something
 * 			check if the sim was end if its was end we dont we the put
 * 			or put timestamp_in_ms X status.
 */
static void	ft_put_status(time_t time, int id, char *str, t_philo *p)
{
	if (ft_stop_sim(p))
		return ;
	printf("%ld %d %s", time, id, str);
}

/**
 * @brief ft_put_died everytime a philosopher do something
 * 			put timestamp_in_ms X status.
 */
static int	ft_put_died(time_t time, int id, char *str)
{
	printf("%ld %d %s", time, id, str);
	return (0);
}

/**
 * @brief ft_status get the actual time of the simulation
 *		and check the signal to/in t_philo and print the good string.
 *		If (signal == EATING) its changed the last_eat time of the philo
 */
void	ft_status(t_philo *p, t_sig signal, time_t *timer)
{
	time_t	sim_t;

	pthread_mutex_lock(&p->arg->write_lock);
	*timer = get_time_in_ms();
	sim_t = *timer - p->start_time;
	if (signal == FORK)
		ft_put_status(sim_t, p->id, "has taken a fork\n", p);
	else if (signal == EATING)
		ft_put_status(sim_t, p->id, "is eating\n", p);
	else if (signal == SLEEPING)
		ft_put_status(sim_t, p->id, "is sleeping\n", p);
	else if (signal == THINKING)
		ft_put_status(sim_t, p->id, "is thinking\n", p);
	else if (signal == DIED)
		ft_put_died(sim_t, p->id, "died\n");
	pthread_mutex_unlock(&p->arg->write_lock);
	if (signal == EATING)
	{
		pthread_mutex_lock(&p->arg->eat_lock);
		p->last_eat = *timer;
		pthread_mutex_unlock(&p->arg->eat_lock);
	}
}
