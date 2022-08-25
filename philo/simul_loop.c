/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:16:23 by yolee             #+#    #+#             */
/*   Updated: 2022/08/25 03:34:30 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	thread_detach_all(t_simul_data *simul_data,
		t_table_data *table_data)
{
	int	loop;

	loop = 0;
	while (loop < simul_data->num_philo)
	{
		pthread_detach(table_data->philosophers[loop].philo);
		loop++;
	}
}

static struct timeval	calc_starve_time(t_philo_data *philo_data)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (diff_timeval(time_now, philo_data->eat_time));
}

static int	is_completed_meal(t_simul_data *simul_data,
		t_philo_data *philo_data)
{
	if (simul_data->is_min_eat_time_specified == 1)
		if (philo_data->eat_count < simul_data->min_eat_time)
			return (TRUE);
	return (FALSE);
}

static void	check_philo(t_simul_data *simul_data, t_table_data *table_data)
{
	int				loop;
	int				min_eat_flag;
	int				time_now;
	struct timeval	starve_time;

	loop = 0;
	min_eat_flag = 1;
	while (loop < simul_data->num_philo)
	{
		time_now = conv_timeval_to_ms(calc_curr_time(simul_data));
		starve_time = calc_starve_time(&table_data->philosophers[loop]);
		if (comp_timeval(starve_time,
				conv_ms_to_timeval(simul_data->time_to_die)))
		{
			printf("%dms %d died\n", time_now, loop);
			simul_data->is_ended = 1;
			return ;
		}
		if (is_completed_meal(simul_data, &table_data->philosophers[loop]))
			min_eat_flag = 0;
		loop++;
	}
	if (simul_data->is_min_eat_time_specified == 1 && min_eat_flag == 1)
		simul_data->is_ended = 1;
}

void	simul_loop(t_simul_data *simul_data, t_table_data *table_data)
{
	int	loop;

	pthread_mutex_unlock(&simul_data->start_mutex);
	gettimeofday(&simul_data->start_time, NULL);
	loop = 0;
	while (loop < simul_data->num_philo)
	{
		table_data->philosophers[loop].eat_time = simul_data->start_time;
		loop++;
	}
	pthread_mutex_init(&simul_data->print_mutex, NULL);
	while (!simul_data->is_ended)
	{
		check_philo(simul_data, table_data);
	}
	thread_detach_all(simul_data, table_data);
}
