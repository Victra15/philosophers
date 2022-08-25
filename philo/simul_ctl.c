/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul_ctl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 03:07:31 by yolee             #+#    #+#             */
/*   Updated: 2022/08/26 04:55:16 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_mutex_lock(t_simul_data *simul_data)
{
	pthread_mutex_init(&simul_data->start_mutex, NULL);
	pthread_mutex_lock(&simul_data->start_mutex);
}

int	print_with_mutex(char *print_msg, t_simul_data *simul_data, int philo_idx)
{
	int	time_now;

	pthread_mutex_lock(&simul_data->print_mutex);
	if (simul_data->is_ended)
		return (1);
	time_now = conv_timeval_to_ms(calc_curr_time(simul_data));
	printf(print_msg, time_now, philo_idx);
	pthread_mutex_unlock(&simul_data->print_mutex);
	return (0);
}

int	print_eat_with_mutex(char *print_msg,
	t_simul_data *simul_data,
	int philo_idx,
	t_philo_data *philo_data)
{
	int	time_now;

	pthread_mutex_lock(&simul_data->print_mutex);
	if (simul_data->is_ended)
		return (1);
	time_now = conv_timeval_to_ms(calc_curr_time(simul_data));
	gettimeofday(&philo_data->eat_time, NULL);
	if (philo_data->simul_data->is_min_eat_time_specified)
		philo_data->eat_count++;
	printf(print_msg, time_now, philo_idx);
	pthread_mutex_unlock(&simul_data->print_mutex);
	return (0);
}
