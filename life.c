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

long	life_time(void)
{
	return (time_now() - life_get()->begin);
}

void	life_set(t_life *set)
{
	int	i;

	set->alive = On;
	i = -1;
	while (++i < 2)
	{
		if (pthread_mutex_init(&set->locker[i], NULL) != 0)
			printf("error creating mutex\n");
	}
	set->begin = time_now();
}

void	life_is_going(t_life *set, char **argv)
{
	life_command(set, argv);
}

void	life_pop(t_life *set)
{
	int	i;

	if (set->philo)
		free(set->philo);
	i = -1;
	while (++i < 2)
		pthread_mutex_destroy(&set->locker[i]);
}
