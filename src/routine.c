/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/10 15:17:56 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"



void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	p->last_meal = get_actual_time();
	while (!check_dead_philos(p->link_b))
	{
		if (pthread_mutex_lock(p->left) == 0)
		{	
			printf("1 PASSOU AQUI\n");
			if (pthread_mutex_lock(p->right) == 0)
			{
				printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);

				p->last_meal = get_actual_time();
				p->meals++;
				printf("%lld %d is eating\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				usleep(p->link_b->time_to_eat * 1000);

				pthread_mutex_unlock(p->right);
				pthread_mutex_unlock(p->left);

				if (is_dead(p) || check_meals(p->link_b))
					break ;

				printf("%lld %d is sleeping\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
				usleep(p->link_b->time_to_sleep * 1000);

				if (is_dead(p) || check_meals(p->link_b))
					break ;

				printf("%lld %d is thinking\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
				usleep(p->link_b->time_to_eat / 2);

				if (is_dead(p) || check_meals(p->link_b))
					break ;	
			}
			else
				printf("2 PASSOU AQUI\n");
			
			pthread_mutex_unlock(p->right);
			pthread_mutex_unlock(p->left);
		}
		if (is_dead(p) || check_meals(p->link_b))
			break ;	
	}
	if (p->die)
		printf("%lld %d died\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
	return (NULL);
}
