/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:12:14 by lde-cast          #+#    #+#             */
/*   Updated: 2024/01/11 12:12:48 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_life	*tale;

	if (argc > 4 && argv)
	{
		tale = life_get();
		life_set(tale);
		life_is_going(tale, argv);
		life_pop(tale);
	}
	else
		printf("arguments passed are wrong\n");
	return (0);
}
