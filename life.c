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

void	life_set(t_life *set)
{
	set->alive = On;
	if (pthread_mutex_init(&set->time_to_die, NULL) != 0)
		printf("error creating mutex\n");
	set->begin = time_now();
	set->fork = NULL;
}

void	life_pop(t_life *set)
{
	int	i;

	if (set->philo)
		free(set->philo);
	pthread_mutex_destroy(&set->time_to_die);
	i = -1;
	while (++i < set->philo_max)
		pthread_mutex_destroy(&set->fork[i]);
}
