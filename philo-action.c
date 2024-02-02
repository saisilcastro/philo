/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:11:49 by mister-code       #+#    #+#             */
/*   Updated: 2024/02/01 20:21:22 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static inline char	*philo_msg(int act)
{
	if (act == 2)
		return ("is thinking\n");
	else if (act == 1)
		return ("is sleeping\n");
	return ("is eating\n");
}

t_status	philo_take_fork(t_life *life, t_philo *man)
{
	t_philo	*neighbor;
	if (man->hand & (1 << LEFT_HAND) && man->hand & (1 << RIGHT_HAND))
		return (printf("%ld %i took a fork\n", life_time(), man->id), On);
	if (!(man->hand & (1 << LEFT_HAND)))
	{
		pthread_mutex_lock(&life->locker[1]);
		neighbor = &life->philo[index_get(man->id - 1, life->philo_max - 1)];
		neighbor->hand &= ~(1 << RIGHT_HAND);
		man->hand |= (1 << LEFT_HAND);
		pthread_mutex_unlock(&life->locker[1]);
	}
	if (!(man->hand & (1 << RIGHT_HAND)))
	{
		pthread_mutex_lock(&life->locker[1]);
		neighbor = &life->philo[index_get(man->id + 1, life->philo_max - 1)];
		neighbor->hand &= ~(1 << LEFT_HAND);
		man->hand |= (1 << RIGHT_HAND);
		pthread_mutex_unlock(&life->locker[1]);
	}
	return (Off);
}

void	philo_action(t_life *life, t_philo *man)
{
	if (!philo_take_fork(life, man))
		return ;
	if (timer_get(&man->wait[man->act]))
	{
		printf("%ld %i %s", life_time(), man->id + 1, philo_msg(man->act));
		man->act++;
		if (man->act > 2)
			man->act = 0;
		timer_set(&man->wait[man->act]);
	}
}

void	has_philo_died(t_life *life, t_philo *man)
{
	if (timer_get(man->die))
	{
		if (life->alive == On)
		{
			pthread_mutex_lock(&life->locker[0]);
			printf("%li %i has died\n", life_time(), man->id);
			life->alive = Off;
			pthread_mutex_unlock(&life->locker[0]);
		}
	}
}
