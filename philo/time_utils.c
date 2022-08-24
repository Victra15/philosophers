/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 03:15:59 by yolee             #+#    #+#             */
/*   Updated: 2022/08/24 04:15:19 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

struct timeval	diff_timeval(struct	timeval later, struct timeval earlier)
{
	struct timeval	diff;

	diff.tv_sec = later.tv_sec - earlier.tv_sec;
	diff.tv_usec = later.tv_usec - earlier.tv_usec;
	if (diff.tv_sec > 0 && diff.tv_usec < 0)
	{
		diff.tv_sec--;
		diff.tv_usec += 1000000;
	}
	return (diff);
}

int	comp_timeval(struct	timeval later, struct timeval earlier)
{
	if (later.tv_sec > earlier.tv_sec)
		return (TRUE);
	else
	{
		if (later.tv_sec == earlier.tv_sec)
			if (later.tv_usec > earlier.tv_usec)
				return (TRUE);
		return (FALSE);
	}
}

struct timeval	conv_ms_to_timeval(int time_ms)
{
	struct timeval	time_ev;

	time_ev.tv_sec = time_ms / 1000;
	time_ev.tv_usec = time_ms * 1000 % 1000000;
	return (time_ev);
}

int	conv_timeval_to_ms(struct timeval time_ev)
{
	int	time_ms;

	time_ms = (time_ev.tv_sec * 1000) + (time_ev.tv_usec / 1000);
	return (time_ms);
}

struct timeval	calc_curr_time(t_philo_data *philo_data)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (diff_timeval(time_now, philo_data->start_time));
}
