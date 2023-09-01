/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/01 05:44:53 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	check_dead_philos(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->nbr_p)
	{
		pthread_mutex_lock(&base->philo_id[i].fork->mutex[i]);
		if (base->philo_id[i].die == true)
		{
			pthread_mutex_unlock(&base->philo_id[i].fork->mutex[i]);
			return (true);
		}
		pthread_mutex_unlock(&base->philo_id[i].fork->mutex[i]);
		i++;
	}
	return (false);
}
