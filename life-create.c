/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:04:11 by mister-code       #+#    #+#             */
/*   Updated: 2024/02/09 16:28:35 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static inline t_status	life_fork_start(t_life *set)
{
	int	i;

	set->fork = malloc((set->philo_max) * sizeof(pthread_mutex_t));
	if (!set->fork)
		return (Off);
	i = -1;
	while (++i < set->philo_max)
	{
		if (pthread_mutex_init(&set->fork[i], NULL) != 0)
			printf("error creating mutex\n");
	}
	return (On);
}

static inline t_status	life_create(t_life *set)
{
	int		i;

	if (!life_fork_start(set))
		return (Off);
	set->philo = malloc((set->philo_max) * sizeof(t_philo));
	if (!set->philo)
		return (Off);
	i = -1;
	while (++i < set->philo_max)
	{
		philo_set(&set->philo[i], i, set->action);
		set->philo[i].left_hand = &set->fork[i];
		set->philo[i].right_hand = &set->fork[(i + 1) % set->philo_max];
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

	if (!set)
		return ;
	i = -1;
	while (++i < set->philo_max)
		pthread_join(set->philo[i].core, NULL);
	pthread_join(set->leader, NULL);
}

static inline t_status	valid_argument(t_life *set)
{
	return (set->philo_max && set->action->die
		&& set->action->eat && set->action->sleep);
}

void	life_is_going(t_life *set, char **argv)
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
	if (!valid_argument(set))
	{
		printf("invalid argument\n");
		return ;
	}
	if (!life_create(set))
		set->alive = Off;
	life_join(set);
}
