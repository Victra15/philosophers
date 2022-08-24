/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:44:36 by yolee             #+#    #+#             */
/*   Updated: 2022/08/24 16:26:23 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philo_data(t_simul_data *simul_data,
		t_table_data *table_data,
		int philo_idx)
{
	t_philo_data	*philo_data;

	philo_data = &table_data->philosophers[philo_idx];
	philo_data->simul_data = simul_data;
	philo_data->philo_idx = philo_idx;
	gettimeofday(&philo_data->eat_time, NULL);
	philo_data->eat_count = 0;
	gettimeofday(&philo_data->start_time, NULL);
	if (philo_idx - 1 >= 0)
		philo_data->l_fork = &table_data->forks[philo_idx - 1];
	else
		philo_data->l_fork = &table_data->forks[simul_data->num_philo - 1];
	philo_data->r_fork = &table_data->forks[philo_idx];
}

static void	*philo_act(void *data)
{
	t_philo_data	*philo_data;

	philo_data = (t_philo_data *)data;
	while (!philo_data->simul_data->is_ended)
	{
		if (!philo_data->simul_data->is_ended)
			thinking(philo_data);
		if (!philo_data->simul_data->is_ended)
			eating(philo_data);
		if (!philo_data->simul_data->is_ended)
			sleeping(philo_data);
	}
	return (NULL);
}

static void	simul_start(t_simul_data *simul_data, t_table_data *table_data)
{
	int	loop;

	loop = 0;
	while (loop < simul_data->num_philo)
	{
		pthread_mutex_init(&table_data->forks[loop], NULL);
		loop++;
	}
	loop = 0;
	while (loop < simul_data->num_philo)
	{
		init_philo_data(simul_data, table_data, loop);
		loop++;
	}
	loop = 0;
	while (loop < simul_data->num_philo)
	{
		pthread_create(&table_data->philosophers[loop].philo,
			NULL,
			philo_act,
			(void *)&table_data->philosophers[loop]);
		loop++;
	}
	simul_loop(simul_data, table_data);
}

static int	init_simul_data(int argc,
		char **argv,
		t_simul_data *simul_data,
		t_table_data *table_data)
{
	simul_data->num_philo = ft_atoi(argv[1]);
	simul_data->time_to_die = ft_atoi(argv[2]);
	simul_data->time_to_eat = ft_atoi(argv[3]);
	simul_data->time_to_sleep = ft_atoi(argv[4]);
	simul_data->is_min_eat_time_specified = 0;
	simul_data->is_ended = 0;
	if (argc == 6)
	{
		simul_data->min_eat_time = ft_atoi(argv[5]);
		simul_data->is_min_eat_time_specified = 1;
	}
	table_data->philosophers = (t_philo_data *)malloc(
			sizeof(t_philo_data) * simul_data->num_philo);
	if (table_data->philosophers == NULL)
		return (0);
	table_data->forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * simul_data->num_philo);
	if (table_data->forks == NULL)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_simul_data	simul_data;
	t_table_data	table_data;

	if (argc == 5 || argc == 6)
	{
		if (!init_simul_data(argc, argv, &simul_data, &table_data))
			return (1);
		simul_start(&simul_data, &table_data);
	}
	else
		write(2, "invalid arguments num\n", 23);
	return (0);
}
