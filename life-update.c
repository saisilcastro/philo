/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:05:47 by mister-code       #+#    #+#             */
/*   Updated: 2024/02/02 20:24:20 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*life_action(void *data)
{
	t_life		*life;

	life = life_get();
	while (life->alive == On)
	{
		philo_eat(data);
		if (life->alive == Off)
			return (NULL);
		philo_sleep(data);
		if (life->alive == Off)
			return (NULL);
		philo_think(data);
		if (life->alive == Off)
			return (NULL);
	}
	return (NULL);
}

void	*main_loop(void *data)
{
	t_life	*life;
	int		i;

	life = data;
	while (life->alive == On)
	{
		i = -1;
		while (++i < life->philo_max)
		{
			pthread_mutex_lock(&life->time_to_die);
			if (timer_get(life->philo[i].die) || \
			(life->action->eat_max > 0 && \
			life->philo[i].has_eaten >= life->action->eat_max))
			{
				life->alive = Off;
				printf("%ld %i has died\n", life_time(), life->philo[i].id + 1);
				pthread_mutex_unlock(&life->time_to_die);
				pthread_mutex_unlock(life->philo->right_hand);
				return (NULL);
			}
			pthread_mutex_unlock(&life->time_to_die);
		}
	}
	return (NULL);
}
