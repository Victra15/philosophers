/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:16:23 by yolee             #+#    #+#             */
/*   Updated: 2022/08/26 14:34:19 by yolee            ###   ########.fr       */
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

	loop = 0;
	min_eat_flag = 1;
	while (loop < simul_data->num_philo)
	{
		if (print_die_with_mutex("%dms %d died\n",
				simul_data,
				&table_data->philosophers[loop]))
			return ;
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
