/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-timer-init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:57:45 by lde-cast          #+#    #+#             */
/*   Updated: 2024/01/11 15:18:42 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_set(t_philo *set, int id, t_action *action)
{
	set->id = id;
	set->has_eaten = 0;
	set->left_hand = NULL;
	set->right_hand = NULL;
	timer_start(&set->wait[0], action->eat);
	timer_start(&set->wait[1], action->sleep);
	timer_start(&set->wait[2], 0);
	timer_start(set->die, action->die);
}

void	philo_message(t_philo *set, char *msg)
{
	t_life	*life;

	if (life_get()->action->eat_max && philo_satiated(set))
		return ;
	life = life_get();
	pthread_mutex_lock(&life->message);
	printf("%ld %d %s\n", life_time(), set->id + 1, msg);
	pthread_mutex_unlock(&life->message);
}

void	philo_die(t_philo *set, char *msg)
{
	t_life	*life;

	life = life_get();
	pthread_mutex_lock(&life->message);
	printf("%ld %d %s\n", life_time(), set->id + 1, msg);
	pthread_mutex_unlock(&life->message);
}

t_status	philo_satiated(t_philo *set)
{
	t_life	*life;

	life = life_get();
	pthread_mutex_lock(&life->satiated);
	if (set->has_eaten >= life->action->eat_max)
	{
		pthread_mutex_unlock(&life->satiated);
		return (On);
	}
	pthread_mutex_unlock(&life->satiated);
	return (Off);
}
