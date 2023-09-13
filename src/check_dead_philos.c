/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/13 14:41:55 by ialves-m         ###   ########.fr       */
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

bool	is_dead(t_base *b, int id)
{
	pthread_mutex_lock(&b->dead_philo_mutex);
	if (b->philo_id[id].last_meal != 0 && get_actual_time() - b->philo_id[id].last_meal > b->time_to_die && b->dead_philo_detected != true)
	{
		b->philo_id[id].die = true;
		//if (check_meals(b) != true)
		printf("%lld %d died\n", (get_actual_time() - b->philo_id[id].last_meal), id+1);
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
	while (1)
	{
		if (check_meals(base))
			return ;
		while (i < base->nbr_philos)
		{
			if (is_dead(base, i) == true)
			{
				pthread_mutex_lock(&base->dead_philo_mutex);
				base->dead_philo_detected = true;
				pthread_mutex_unlock(&base->dead_philo_mutex);
				return ;
			}	
			i++;
		}
		i = 0;
	}

}

bool	check_deads_or_meals(t_philo *p)
{
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	if (p->die == true || p->link_b->dead_philo_detected == true || check_meals(p->link_b) == true)
	{
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		return (true);
	}
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
	return (false);
}
