/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:05:47 by mister-code       #+#    #+#             */
/*   Updated: 2024/02/05 17:10:33 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*life_action(void *data)
{
	if (!data)
		return (NULL);
	while (!life_is_over())
	{
		philo_eat(data);
		philo_sleep(data);
		philo_think(data);
	}
	return (NULL);
}

static inline t_status	has_eaten_enough(t_life *life)
{
	int	i;

	if (life->action->eat_max == 0)
		return (Off);
	i = -1;
	pthread_mutex_lock(&life->full);
	while (++i < life->philo_max)
	{
		if (!philo_satiated(&life->philo[i]))
		{
			pthread_mutex_unlock(&life->full);
			return (Off);
		}
	}
	pthread_mutex_unlock(&life->full);
	return (On);
}

void	*main_loop(void *data)
{
	t_life	*life;
	int		i;

	life = data;
	while (!life_is_over())
	{
		i = -1;
		while (++i < life->philo_max)
		{
			pthread_mutex_lock(&life->time_to_die);
			if (timer_get(life->philo[i].die))
			{
				if (life->alive)
					philo_die(&life->philo[i], "has died");
				if (life->philo_max == 1)
					pthread_mutex_unlock(life->philo->left_hand);
				life->alive = Off;
			}
			if (has_eaten_enough(life))
				life->alive = Off;
			pthread_mutex_unlock(&life->time_to_die);
		}
	}
	return (NULL);
}
