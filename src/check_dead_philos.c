/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/11 16:52:21 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	check_meals(t_base *b)
{
	int	i;

	i = 0;
	while (i < b->nbr_philos)
	{
		pthread_mutex_lock(&b->meals_mutex);
		if (b->philo_id[i++].meals < b->nbr_meals)
		{
			pthread_mutex_unlock(&b->meals_mutex);
			return (false);
		}
		pthread_mutex_unlock(&b->meals_mutex);
	}
	pthread_mutex_lock(&b->meals_mutex);
	b->nbr_meals_reached = true;
	pthread_mutex_unlock(&b->meals_mutex);
	return (true);
}

bool	is_dead(t_philo *p, int id)
{
	pthread_mutex_lock(&p->link_b->meals_mutex);
	if ((get_actual_time() - p->link_b->philo_id[id].last_meal) >= p->link_b->time_to_die)
	{
		p->die = true;
		pthread_mutex_unlock(&p->link_b->meals_mutex);
		return (true);
	}
	pthread_mutex_unlock(&p->link_b->meals_mutex);
	return (false);	
}

bool	check_dead_philos(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->nbr_philos)
	{
		pthread_mutex_lock(&base->meals_mutex);
		if (is_dead(base->philo_id, base->philo_id[i].id))
		{
			base->philo_id[i].die = true;
		}
		printf("Time: %lld\n", get_actual_time());
		pthread_mutex_unlock(&base->meals_mutex);
		i++;
	}
	i = 0;
	return (true);
}
