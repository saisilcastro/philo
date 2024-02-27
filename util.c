/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_atoul_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:38:15 by lde-cast          #+#    #+#             */
/*   Updated: 2024/01/11 11:23:09 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static inline int	base_get(char base)
{
	if (base >= 0x30 && base <= 0x39)
		return (base - 0x30);
	else if (base >= 0x41 && base <= 0x46)
		return (base - 0x41 + 10);
	else if (base >= 0x51 && base < 0x56)
		return (base - 0x51 + 10);
	return (0);
}

unsigned long	pl_atoul_base(char *str, unsigned char base)
{
	long	nb;

	nb = 0;
	while (*str)
	{
		nb = (nb * base) + base_get(*str);
		str++;
	}
	return (nb);
}

int	index_get(int n, int max)
{
	if (n < 0)
		return (max);
	if (n >= max)
		return (0);
	return (n);
}

long	life_time(void)
{
	return (time_now() - life_get()->begin);
}
