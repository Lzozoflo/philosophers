/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcretin <fcretin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:05:00 by fcretin           #+#    #+#             */
/*   Updated: 2025/04/04 18:25:22 by fcretin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <pthread.h>
# define MY_SIG_ERROR 1

# define START_CONTINUE 0
# define STOP 1

# define NO_COUNT -42

# define AVAILABLE 1
# define UNAVAILABLE 0

typedef enum e_sig
{
	FORK = 2,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}			t_sig;

typedef struct s_arg
{
	int				n_philo;
	int				eat_count;
	int				has_eat;
	time_t			start_time;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	start;
	pthread_mutex_t	stop_sim;
	pthread_mutex_t	write_lock;
	__useconds_t	tt_die;
	__useconds_t	tt_eat;
	__useconds_t	tt_sleep;
}				t_arg;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	pthread_mutex_t	l_fork;
	int				bl_fork;
	pthread_mutex_t	*r_fork;
	int				*br_fork;
	int				stop;
	time_t			last_eat;
	t_arg			*arg;
	int				eat_count;
	__useconds_t	tt_die;
	__useconds_t	tt_eat;
	__useconds_t	tt_sleep;
	time_t			start_time;
}				t_philo;

typedef struct s_data
{
	t_philo	*p;
	t_arg	arg;
}				t_data;

/*
 *--------------src/utils/ft_clear.c
 */

int		ft_clear(t_data *data, int nb);
void	ft_mutex_destroy_arg(t_arg *arg, int nb);

/*
 *--------------src/utils/ft_handle_fork.c
*/

int		ft_unlock_mutex_fork(t_philo *p);
void	handle_fork(t_philo *p);

/*
 *--------------src/utils/ft_param.c
 */

int		ft_param(int ac, char **av, t_arg *arg);

/*
 *--------------src/utils/ft_print_status.c
 */

void	ft_status(t_philo *p, t_sig signal, time_t *timer);

/*
*--------------src/utils/ft_sim_utils.c
*/

int		ft_stop_sim(t_philo *p);
int		ft_watch_time(t_philo *p, t_data *data);
void	ft_pthread_join(t_data *d);
void	ft_stop_all(t_data *data);

/*
 *--------------src/utils/ft_time.c
*/

time_t	get_time_in_ms(void);
void	ft_no_delay(t_data *data);
void	ft_usleep(time_t time, __useconds_t tt_some, t_philo *p);

/*
 *--------------src/ft_diogenes_of_sinope.c
 */

void	*ft_diogenes_of_sinope(void *ptr_p);

/*
 *--------------src/ft_init.c
 */

int		ft_init(t_arg *arg, t_philo *p, t_data *data);

/*
 *--------------src/ft_sim.c
 */

int		ft_start_sim(t_data *d);

/*
 *--------------src/ft_state.c
 */

void	ft_first_thinking(t_philo *p);
void	ft_thinking(t_philo *p);
void	ft_sleeping(t_philo *p);
int		ft_get_fork(t_philo *p, int *count);

#endif
