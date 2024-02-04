/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:05:47 by mister-code       #+#    #+#             */
/*   Updated: 2024/02/04 01:46:45 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*life_action(void *data)
{
	t_life		*life;

	if (!data)
		return (NULL);
	(void)data;
	life = life_get();
	while (life->alive)
	{
	}
	printf("action finished\n");
	return (NULL);
}

//static inline t_status	has_eaten_enough(t_life *life)
//{
//	int			max;
//	int			i;

//	if (life->action->eat_max == 0)
//		return (Off);
//	max = 0;
//	i = -1;
//	while (++i < life->philo_max)
//	{
//		if (life->philo[i].has_eaten == life->action->eat_max)
//			max++;
//	}
//	if (max == life->philo_max)
//		return (On);
//	return (Off);
//}

void	*main_loop(void *data)
{
	t_life	*life;
	//int		i;

	life = data;
	while (1)
	{
		if (!pthread_mutex_lock(&life->time_to_die))
		{
			printf("dying\n");
			life->alive = Off;
			pthread_mutex_unlock(&life->time_to_die);
		}
		if (life->alive == Off)
			break ;
		if (pthread_mutex_unlock(&life->time_to_die))
			pthread_mutex_unlock(&life->time_to_die);
	}
	if (pthread_mutex_unlock(&life->time_to_die))
		pthread_mutex_unlock(&life->time_to_die);
	life_pop(life);
	return (NULL);
}
