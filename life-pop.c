/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 00:49:08 by lde-cast          #+#    #+#             */
/*   Updated: 2024/02/05 16:43:11 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	life_pop(t_life *set)
{
	int	i;

	if (set->fork)
	{
		i = -1;
		while (++i < set->philo_max)
			pthread_mutex_destroy(&set->fork[i]);
		free(set->fork);
	}
	pthread_mutex_destroy(&set->satiated);
	pthread_mutex_destroy(&set->full);
	pthread_mutex_destroy(&set->message);
	pthread_mutex_destroy(&set->time_to_die);
	if (set->philo)
		free(set->philo);
}
