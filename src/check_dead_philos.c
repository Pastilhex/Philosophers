/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/10 19:54:18 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	check_dead_meals(t_philo *p)
{
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	if (is_dead(p))
	{
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		return (true);
	}
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
	return (false);
}

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

bool	is_dead(t_philo *p)
{
	if ((get_actual_time() - p->last_meal) >= p->link_b->time_to_die)
	{
		pthread_mutex_lock(&p->link_b->dead_philo_mutex);
		p->die = true;
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
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
		pthread_mutex_lock(&base->dead_philo_mutex);
		if (base->philo_id[i].die == true)
		{
			pthread_mutex_unlock(&base->dead_philo_mutex);
			return (true);
		}
		pthread_mutex_unlock(&base->dead_philo_mutex);
		i++;
	}
	return (false);
}
