/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:11:49 by mister-code       #+#    #+#             */
/*   Updated: 2024/02/04 02:00:39 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

t_status	philo_fork_take(t_philo *set)
{
	if (set->id % 2 == 0)
	{
		pthread_mutex_lock(set->left_hand);
		pthread_mutex_lock(set->right_hand);
		if (life_is_over())
		{
			philo_fork_release(set);
			return (Off);
		}
		printf("%ld %i has taken a fork\n", life_time(), set->id);
		printf("%ld %i has taken a fork\n", life_time(), set->id);
	}
	else
	{
		pthread_mutex_lock(set->right_hand);
		pthread_mutex_lock(set->left_hand);
		if (life_is_over())
		{
			philo_fork_release(set);
			return (Off);
		}
		printf("%ld %i has taken a fork\n", life_time(), set->id);
		printf("%ld %i has taken a fork\n", life_time(), set->id);
	}
	return (On);
}

void	philo_fork_release(t_philo *set)
{
	if (set->id % 2 == 0)
	{
		pthread_mutex_unlock(set->left_hand);
		pthread_mutex_unlock(set->right_hand);
	}
	else
	{
		pthread_mutex_unlock(set->right_hand);
		pthread_mutex_unlock(set->left_hand);
	}
}

t_status	philo_eat(t_philo *set)
{
	if (!philo_fork_take(set))
		return (Off);
	return (On);
}

void	philo_sleep(t_philo *man)
{
	if (life_is_over())
		return ;
	printf("%ld %i is sleeping\n", life_time(), man->id + 1);
	usleep(man->wait[1].interval * 1000);
}

void	philo_think(t_philo *man)
{
	if (life_is_over())
		return ;
	printf("%ld %i is thinking\n", life_time(), man->id + 1);
	usleep(man->wait[2].interval * 1000);
}
