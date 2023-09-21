/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/22 00:07:25 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	check_meals(t_base *b)
{
	int	i;

	i = 0;
	while (i < b->nbr_philos)
	{
		pthread_mutex_lock(&b->dead_philo_mutex);
		if (b->philo_id[i++].meals < b->nbr_meals)
		{
			pthread_mutex_unlock(&b->dead_philo_mutex);
			return (false);
		}
		pthread_mutex_unlock(&b->dead_philo_mutex);
	}
	pthread_mutex_lock(&b->dead_philo_mutex);
	b->nbr_meals_reached = true;
	pthread_mutex_unlock(&b->dead_philo_mutex);
	return (true);
}

void	check_dead_philos(t_base *b)
{
	int	i;

	i = 0;
	while (b->dead_philo_detected == false && b->nbr_meals_reached == false)
	{
		check_meals(b);
		while (i < b->nbr_philos)
		{
			pthread_mutex_lock(&b->dead_philo_mutex);
			if (get_actual_time() - b->philo_id[i].last_meal > b->time_to_die \
				&& b->dead_philo_detected == false)
			{
				printf("%lld %d died\n", \
					(get_actual_time() - b->philo_id[i].last_meal), i + 1);
				b->dead_philo_detected = true;
				pthread_mutex_unlock(&b->dead_philo_mutex);
				return ;
			}
			i++;
			pthread_mutex_unlock(&b->dead_philo_mutex);
		}
		i = 0;
	}
}

void	join_threads(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->nbr_philos)
		pthread_join(base->philo_id[i++].philo_thread, NULL);
}

bool	jump_off(t_philo *p)
{
	usleep(400);
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	if (p->link_b->dead_philo_detected == true
		|| p->link_b->nbr_meals_reached == true)
	{
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		return (true);
	}
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
	return (false);
}
