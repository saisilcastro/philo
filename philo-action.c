/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:11:49 by mister-code       #+#    #+#             */
/*   Updated: 2024/02/02 20:24:32 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

static inline t_status	right_hand(t_philo *man)
{
	int	left;
	int	right;

	if (life_get()->alive == Off)
		return (Off);
	right = pthread_mutex_lock(man->right_hand);
	left = pthread_mutex_lock(man->left_hand);
	if (!right && !left)
	{
		if (life_get()->alive)
		{
			printf("%ld %i has taken a fork\n", life_time(), man->id + 1);
			printf("%ld %i is eating\n", life_time(), man->id + 1);
		}
		man->has_eaten++;
		usleep(man->wait[0].interval * 1000);
		pthread_mutex_unlock(man->right_hand);
		pthread_mutex_unlock(man->left_hand);
		timer_set(man->die);
	}
	return (On);
}

static inline t_status	left_hand(t_philo *man)
{
	int	left;
	int	right;

	if (life_get()->alive == Off)
		return (Off);
	left = pthread_mutex_lock(man->left_hand);
	right = pthread_mutex_lock(man->right_hand);
	if (!left && !right)
	{
		if (life_get()->alive)
		{
			printf("%ld %i has taken a fork\n", life_time(), man->id + 1);
			printf("%ld %i is eating\n", life_time(), man->id + 1);
		}
		man->has_eaten++;
		usleep(man->wait[0].interval * 1000);
		pthread_mutex_unlock(man->left_hand);
		pthread_mutex_unlock(man->right_hand);
		timer_set(man->die);
	}
	return (On);
}

t_status	philo_eat(t_philo *man)
{
	if (life_get()->alive == Off)
		return (Off);
	if (man->id % 2 == 0)
		return (right_hand(man));
	else
		return (left_hand(man));
	return (Off);
}

void	philo_sleep(t_philo *man)
{
	if (life_get()->alive)
		printf("%ld %i is sleeping\n", life_time(), man->id + 1);
	else
	{
		printf("can't sleep\n");
		return ;
	}
	usleep(man->wait[1].interval * 1000);
}

void	philo_think(t_philo *man)
{
	if (life_get()->alive)
		printf("%ld %i is thinking\n", life_time(), man->id + 1);
	else
	{
		printf("can't think\n");
		return ;
	}
	usleep(man->wait[2].interval * 1000);
}
