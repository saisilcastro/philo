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
