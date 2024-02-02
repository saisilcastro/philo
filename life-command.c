/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:03:29 by lde-cast          #+#    #+#             */
/*   Updated: 2024/01/11 15:33:03 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>
#include <unistd.h>

static inline void	*life_action(void *data)
{
	t_life		*life;

	life = life_get();
	while (life->alive == On)
	{
		philo_action(life, data);
		//has_philo_died(life, data);
	}
	return (NULL);
}

static inline void	*main_loop(void *life)
{
	while (((t_life *)life)->alive == On)
	{
	}
	return (NULL);
}

static inline t_status	life_create(t_life *set)
{
	int		i;

	set->philo = malloc((set->philo_max + 1) * sizeof(t_philo));
	if (!set->philo)
		return (Off);
	i = -1;
	while (++i < set->philo_max)
	{
		philo_set(&set->philo[i], i, set->action);
		if (pthread_create(&set->philo[i].core, NULL,
				&life_action, &set->philo[i]) != 0)
			perror("failure creating pthread");
	}
	if (pthread_create(&set->leader, NULL, &main_loop, set) != 0)
		perror("failure creating pthread");
	return (On);
}

static inline void	life_join(t_life *set)
{
	int	i;

	i = -1;
	while (++i < set->philo_max)
		pthread_join(set->philo[i].core, NULL);
	pthread_join(set->leader, NULL);
}

void	life_command(t_life *set, char **argv)
{
	int	i;

	i = -1;
	while (*(++argv) && ++i >= 0)
	{
		if (i == 0)
			set->philo_max = pl_atoul_base(*argv, 10);
		else if (i == 1)
			set->action->die = pl_atoul_base(*argv, 10);
		else if (i == 2)
			set->action->eat = pl_atoul_base(*argv, 10);
		else if (i == 3)
			set->action->sleep = pl_atoul_base(*argv, 10);
		else if (i == 4)
			set->action->eat_max = pl_atoul_base(*argv, 10);
	}
	if (!life_create(set))
		set->alive = Off;
	life_join(set);
}
