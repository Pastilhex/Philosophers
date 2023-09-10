/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/10 15:03:37 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	is_dead(t_philo *p)
{
	long long	time;

	time = last_meal_time(p);
	if (time > p->link_b->time_to_die)
	{
		p->die = true;
		return (true);
	}
	return (false);
}

bool	check_dead_philos(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->nbr_p)
	{
		if (base->philo_id[i].die == true)
		{
			return (true);
		}
		i++;
	}
	return (false);
}
