/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:48:28 by fcretin           #+#    #+#             */
/*   Updated: 2025/03/23 11:00:05 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <limits.h>

/**
 * @brief this ft_atoi_u a atoi unsigned with error
 */
static int	ft_atoi_u(const char *str, int *error)
{
	long	res;
	int		i;

	i = 0;
	res = 0;
	*error = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' && (str[i] < '0' || str[i] > '9'))
		*error = MY_SIG_ERROR;
	if (str[i] == '+' && !str[i + 1])
		*error = MY_SIG_ERROR;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if (res > INT_MAX)
			*error = MY_SIG_ERROR;
	}
	if (str[i])
		*error = MY_SIG_ERROR;
	return ((int)res);
}

/**
 * @brief ft_count_param init the eat_count whit the param in av
 *			or init to -42 to know we dont have limits.
 *
 */
static int	ft_count_param(char **av, t_arg *arg)
{
	int	error;

	if (av[5])
	{
		arg->eat_count = ft_atoi_u(av[5], &error);
		if (error == MY_SIG_ERROR)
			return (1);
		if (arg->eat_count == 0)
			return (1);
	}
	else
	{
		arg->eat_count = NO_COUNT;
	}
	return (0);
}

/**
 * @brief ft_param get argument in arg_struct.
 */
int	ft_param(int ac, char **av, t_arg *arg)
{
	int	error;

	if (ac < 5 || ac > 6)
		return (1);
	arg->n_philo = (unsigned int)ft_atoi_u(av[1], &error);
	if (error == MY_SIG_ERROR || arg->n_philo == 0)
		return (1);
	arg->tt_die = (__useconds_t)ft_atoi_u(av[2], &error);
	if (error == MY_SIG_ERROR)
		return (1);
	arg->tt_eat = (__useconds_t)ft_atoi_u(av[3], &error);
	if (error == MY_SIG_ERROR)
		return (1);
	arg->tt_sleep = (__useconds_t)ft_atoi_u(av[4], &error);
	if (error == MY_SIG_ERROR)
		return (1);
	if (ft_count_param(av, arg))
		return (1);
	return (0);
}
