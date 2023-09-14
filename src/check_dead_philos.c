/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/14 20:27:03 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	what_time(long long current, long long last_meal)
{
	return (current - last_meal);
}

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
	while (b->dead_philo_detected == false && b->nbr_meals_reached == 0)
	{
		check_meals(b);

		while (i < b->nbr_philos)
		{
			pthread_mutex_lock(&b->meals_mutex);
			pthread_mutex_lock(&b->dead_philo_mutex);

			if (what_time(get_actual_time(), b->philo_id[i].last_meal) > b->time_to_die && b->dead_philo_detected == false)
			{
				printf("%lld %d died\n", (get_actual_time() - b->philo_id[i].last_meal), i + 1);
				b->dead_philo_detected = true;
			}

			pthread_mutex_unlock(&b->dead_philo_mutex);
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
