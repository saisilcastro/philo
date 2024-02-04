/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:09:37 by lde-cast          #+#    #+#             */
/*   Updated: 2024/01/10 17:10:49 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static inline long	times_thousand(long i)
{
	return ((i << 10) - (i << 4) - (i << 3));
}

long	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (times_thousand(now.tv_sec) + (now.tv_usec * 1e-3));
}

void	timer_start(t_timer *set, unsigned long interval)
{
	if (!set)
		return ;
	set->interval = interval;
	set->begin = time_now();
}

int	timer_get(t_timer *set)
{
	if (!set)
		return (0);
	if (time_now() - set->begin < set->interval)
		return (0);
	return (1);
}
