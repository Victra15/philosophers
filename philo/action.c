/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:49:54 by yolee             #+#    #+#             */
/*   Updated: 2022/08/26 14:08:43 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(int sleep_time_ms, struct timeval before)
{
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
		usleep(1);
	}
}

void	thinking(t_philo_data *philo_data)
{
	print_with_mutex("%dms %d is thinking\n",
		philo_data->simul_data,
		philo_data->philo_idx);
}

static int	grab_forks(t_philo_data *philo_data)
{
	if (philo_data->philo_idx % 2)
	{
		usleep(philo_data->simul_data->time_to_eat / 2);
		pthread_mutex_lock(philo_data->l_fork);
	}
	else
		pthread_mutex_lock(philo_data->r_fork);
	if (print_with_mutex("%dms %d has taken a fork\n",
			philo_data->simul_data,
			philo_data->philo_idx))
		return (1);
	if (philo_data->philo_idx % 2)
		pthread_mutex_lock(philo_data->r_fork);
	else
		pthread_mutex_lock(philo_data->l_fork);
	if (print_with_mutex("%dms %d has taken a fork\n",
			philo_data->simul_data,
			philo_data->philo_idx))
		return (1);
	return (0);
}

void	eating(t_philo_data *philo_data)
{
	if (grab_forks(philo_data))
		return ;
	if (print_eat_with_mutex("%dms %d is eating\n",
			philo_data->simul_data,
			philo_data->philo_idx,
			philo_data))
		return ;
	ft_sleep(philo_data->simul_data->time_to_eat, philo_data->sleep_time);
	pthread_mutex_unlock(philo_data->l_fork);
	pthread_mutex_unlock(philo_data->r_fork);
}

void	sleeping(t_philo_data *philo_data)
{
	if (print_with_mutex("%dms %d is eating\n",
			philo_data->simul_data,
			philo_data->philo_idx))
		return ;
	ft_sleep(philo_data->simul_data->time_to_sleep, philo_data->sleep_time);
}
