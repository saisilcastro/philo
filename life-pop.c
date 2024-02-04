/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 00:49:08 by lde-cast          #+#    #+#             */
/*   Updated: 2024/02/04 00:58:11 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	life_pop(t_life *set)
{
	if (set->philo)
		free(set->philo);
	if (set->fork)
		free(set->fork);
	if (pthread_mutex_trylock(&set->time_to_die))
		pthread_mutex_unlock(&set->time_to_die);
	pthread_mutex_destroy(&set->time_to_die);
}
