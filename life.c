/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:07:58 by lde-cast          #+#    #+#             */
/*   Updated: 2024/01/11 15:32:26 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <string.h>
#include <stdio.h>

t_life	*life_get(void)
{
	static t_life	life;

	return (&life);
}

t_status	life_is_over(void)
{
	t_life	*life;

	life = life_get();
	pthread_mutex_lock(&life->time_to_die);
	if (life->alive == Off)
	{
		pthread_mutex_unlock(&life->time_to_die);
		return (On);
	}
	pthread_mutex_unlock(&life->time_to_die);
	return (Off);
}

void	life_set(t_life *set)
{
	set->alive = On;
	if (pthread_mutex_init(&set->satiated, NULL) != 0)
		printf("error creating mutex\n");
	if (pthread_mutex_init(&set->full, NULL) != 0)
		printf("error creating mutex\n");
	if (pthread_mutex_init(&set->message, NULL) != 0)
		printf("error creating mutex\n");
	if (pthread_mutex_init(&set->time_to_die, NULL) != 0)
		printf("error creating mutex\n");
	set->fork = NULL;
	set->begin = time_now();
}
