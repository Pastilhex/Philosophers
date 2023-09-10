/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/10 16:13:09 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	check_meals(t_base *b)
{
	int	i;

	i = 0;
	while (i < b->nbr_p)
	{
		pthread_mutex_lock(&b->meals_mutex);
		if (b->philo_id[i++].meals < b->nbr_of_meals)
		{
			pthread_mutex_unlock(&b->meals_mutex);
			return (false);
		}
		pthread_mutex_unlock(&b->meals_mutex);
	}
	return (true);
}
