/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:16:23 by yolee             #+#    #+#             */
/*   Updated: 2022/08/24 04:05:16 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_philo(t_simul_data *simul_data, t_table_data *table_data)
{
	int				loop;
	int				min_eat_flag;
	struct timeval	time_now;
	struct timeval	starve_time;

	loop = 0;
	min_eat_flag = 1;
	while (loop < simul_data->num_philo)
	{
		time_now = calc_curr_time(&table_data->philosophers[loop]);
		starve_time = diff_timeval(time_now,
				table_data->philosophers[loop].eat_time);
		if (comp_timeval(starve_time,
				conv_ms_to_timeval(simul_data->time_to_die)))
			{
				simul_data->is_ended = 1;
			}
		if (simul_data->is_min_eat_time_specified == 1)
			if (table_data->philosophers[loop].eat_count
				< simul_data->min_eat_time)
				min_eat_flag = 0;
		loop++;
	}
	if (min_eat_flag == 0)
		simul_data->is_ended = 1;
}

void	simul_loop(t_simul_data *simul_data, t_table_data *table_data)
{
	while (!simul_data->is_ended)
	{
		check_philo(simul_data, table_data);
	}
}
