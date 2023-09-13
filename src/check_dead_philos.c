/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/13 20:48:03 by ialves-m         ###   ########.fr       */
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

void	check_dead_philos(t_base *b)
{
	int	i;

	i = 0;
	while (1)
	{
		if (check_meals(b) == true)
			return ;
		while (i < b->nbr_philos)
		{
			pthread_mutex_lock(&b->meals_mutex);
			if (b->philo_id[i].last_meal != 0 && get_actual_time() - b->philo_id[i].last_meal > b->time_to_die )
			{
				printf("%lld %d died\n", (get_actual_time() - b->philo_id[i].last_meal), i + 1);
				pthread_mutex_lock(&b->dead_philo_mutex);
				b->dead_philo_detected = true;
				pthread_mutex_unlock(&b->dead_philo_mutex);
				pthread_mutex_unlock(&b->meals_mutex);
				return ;
			}
			pthread_mutex_unlock(&b->meals_mutex);
			i++;
		}
		i = 0;
	}
}

bool	deads_or_meals(t_philo *p)
{
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	if (p->link_b->dead_philo_detected == true)
	{
		printf("%lld %d DEAD DETECTED\n", (get_actual_time() - p->link_b->time_start), p->id);
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		return (true);
	}
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
	
	pthread_mutex_lock(&p->link_b->meals_mutex);
	if (p->link_b->nbr_meals_reached == true)
	{
		pthread_mutex_unlock(&p->link_b->meals_mutex);
		return (true);
	}
	pthread_mutex_unlock(&p->link_b->meals_mutex);
	return (false);
}
