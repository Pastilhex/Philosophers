/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/12 15:47:26 by ialves-m         ###   ########.fr       */
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

bool	check_for_dead_philos(t_philo *p)
{
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	if (p->link_b->dead_philo_detected == true)
	{
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		return (true) ;
	}
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);	
	return (false);
}

bool	is_dead(t_base *b, int id)
{
	pthread_mutex_lock(&b->dead_philo_mutex);
	if ((get_actual_time() - b->philo_id[id].last_meal > b->time_to_die))
	{
		b->philo_id[id].die = true;
		printf("%lld %d died \n", (get_actual_time() - b->philo_id[id].last_meal), id+1);
		pthread_mutex_unlock(&b->dead_philo_mutex);
		return (true);
	}
	pthread_mutex_unlock(&b->dead_philo_mutex);
	return (false);
}

void	check_dead_philos(t_base *base)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&base->dead_philo_mutex);
	while (base->dead_philo_detected != true)
	{
		pthread_mutex_unlock(&base->dead_philo_mutex);
		while (i < base->nbr_philos)
		{
			if (is_dead(base, i) == true)
				base->dead_philo_detected = true;
			i++;
		}
		i = 0;
		pthread_mutex_lock(&base->dead_philo_mutex);
	}
	pthread_mutex_unlock(&base->dead_philo_mutex);
}
