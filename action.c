/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:49:54 by yolee             #+#    #+#             */
/*   Updated: 2022/08/24 15:40:30 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_simul_ended(t_philo_data *philo_data)
{
	if ()
}

void	ft_sleep(int sleep_time_ms)
{
	struct timeval	before;
	struct timeval	after;
	struct timeval	diff;
	struct timeval	sleep_time_ev;

	sleep_time_ev = conv_ms_to_timeval(sleep_time_ms);
	gettimeofday(&before, NULL);
	gettimeofday(&after, NULL);
	diff = diff_timeval(after, before);
	while (comp_timeval(sleep_time_ev, diff))
	{
		gettimeofday(&after, NULL);
		diff = diff_timeval(after, before);
	}
}

void	thinking(t_philo_data *philo_data)
{
	int				time_now;
	int				philo_idx;

	philo_idx = philo_data->philo_idx;
	time_now = conv_timeval_to_ms(calc_curr_time(philo_data));
	printf("%dms %d is thinking\n", time_now, philo_idx);
}

void	eating(t_philo_data *philo_data)
{
	int				time_now;
	int				philo_idx;

	philo_idx = philo_data->philo_idx;
	pthread_mutex_lock(philo_data->l_fork);
	time_now = conv_timeval_to_ms(calc_curr_time(philo_data));
	printf("%dms %d has taken a fork\n", time_now, philo_data->philo_idx);
	pthread_mutex_lock(philo_data->r_fork);
	time_now = conv_timeval_to_ms(calc_curr_time(philo_data));
	printf("%dms %d has taken a fork\n", time_now, philo_data->philo_idx);
	printf("%dms %d is eating\n", time_now, philo_idx);
	ft_sleep(philo_data->simul_data->time_to_eat);
	pthread_mutex_unlock(philo_data->l_fork);
	pthread_mutex_unlock(philo_data->r_fork);
}

void	sleeping(t_philo_data *philo_data)
{
	int				time_now;
	int				philo_idx;

	philo_idx = philo_data->philo_idx;
	time_now = conv_timeval_to_ms(calc_curr_time(philo_data));
	printf("%dms %d is sleeping\n", time_now, philo_idx);
	ft_sleep(philo_data->simul_data->time_to_sleep);
}
