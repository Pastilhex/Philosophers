/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/10 16:38:52 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"



void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;

	pthread_mutex_lock(&p->link_b->meals_mutex);
	p->last_meal = get_actual_time();
	pthread_mutex_unlock(&p->link_b->meals_mutex);

	while (!check_dead_philos(p->link_b))
	{
		if (pthread_mutex_lock(p->left) == 0)
		{	
			if (p->link_b->nbr_p > 1 && pthread_mutex_lock(p->right) == 0)
			{
				printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);

				printf("%lld %d is eating\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				usleep(p->link_b->time_to_eat * 1000);

				pthread_mutex_lock(&p->link_b->meals_mutex);
				p->last_meal = get_actual_time();
				p->meals++;
				pthread_mutex_unlock(&p->link_b->meals_mutex);

				pthread_mutex_unlock(p->right);
				pthread_mutex_unlock(p->left);

				if (check_dead_meals(p))
					break ;

				printf("%lld %d is sleeping\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
				usleep(p->link_b->time_to_sleep * 1000);

				if (check_dead_meals(p))
					break ;

				printf("%lld %d is thinking\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
				usleep(p->link_b->time_to_eat / 2);

				if (check_dead_meals(p))
					break ;
			}
		}
		if (is_dead(p) || check_meals(p->link_b))
			break ;	
	}
	if (p->die)
		printf("%lld %d died\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
	return (NULL);
}
