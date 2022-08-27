/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:44:53 by yolee             #+#    #+#             */
/*   Updated: 2022/08/27 17:45:48 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define TRUE 1
# define FALSE 0
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_simul_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eat_time;
	int				is_min_eat_time_specified;
	int				is_ended;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	print_mutex;
	struct timeval	start_time;
}t_simul_data;

typedef struct s_philo_data
{
	t_simul_data	*simul_data;
	pthread_t		philo;
	int				philo_idx;
	struct timeval	sleep_time;
	struct timeval	eat_time;
	int				eat_count;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}t_philo_data;

typedef struct s_table_data
{
	t_philo_data	*philosophers;
	pthread_mutex_t	*forks;
}t_table_data;

int				ft_atoi(const char *str);
int				calc_ms(struct timeval after, struct timeval before);
void			ft_sleep(int sleep_time_ms, struct timeval *before);

int				thinking(t_philo_data *philo_data);
int				eating(t_philo_data *philo_data);
int				sleeping(t_philo_data *philo_data);

void			simul_loop(t_simul_data *simul_data, t_table_data *table_data);

struct timeval	diff_timeval(struct	timeval later, struct timeval earlier);
int				comp_timeval(struct	timeval later, struct timeval earlier);
struct timeval	conv_ms_to_timeval(int time_ms);
int				conv_timeval_to_ms(struct timeval time_ev);
struct timeval	calc_curr_time(t_simul_data *simul_data);

void			start_mutex_lock(t_simul_data *simul_data);
int				print_with_mutex(char *print_msg,
					t_simul_data *simul_data,
					int philo_idx,
					t_philo_data *philo_data);
int				print_eat_with_mutex(char *print_msg,
					t_simul_data *simul_data,
					int philo_idx,
					t_philo_data *philo_data);
int				print_die_with_mutex(char *print_msg,
					t_simul_data *simul_data,
					t_philo_data *philo_data);
#endif
