/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/11 21:07:39 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*spy_routine(void *arg)
{
	t_base	*b;

	b = arg;
	while (1)
	{
		check_dead_philos(b);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	
	pthread_mutex_lock(&p->link_b->meals_mutex);
	p->last_meal = get_actual_time();
	pthread_mutex_unlock(&p->link_b->meals_mutex);
	
	if ((p->id + 1) % 2 == 0)
		usleep(p->link_b->time_to_eat / 2);

	while (check_dead_philos(p->link_b) != true)
	{
		if (pthread_mutex_lock(p->left) == 0)
		{	
			if (p->link_b->nbr_philos > 1 && pthread_mutex_lock(p->right) == 0)
			{
				printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);

				pthread_mutex_lock(&p->link_b->meals_mutex);
				p->last_meal = get_actual_time();
				p->meals++;
				pthread_mutex_unlock(&p->link_b->meals_mutex);
				
				printf("%lld %d is eating\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				usleep(p->link_b->time_to_eat * 1000);
			
				pthread_mutex_unlock(p->right);
			}
			pthread_mutex_unlock(p->left);

			//Only for more then 1 philo
			if (p->link_b->nbr_philos > 1)
			{
				printf("%lld %d is sleeping\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
				usleep(p->link_b->time_to_sleep * 1000);

				printf("%lld %d is thinking\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
				usleep(p->link_b->time_to_eat / 10);
			}
			// Check if 1 only Philo died
			if (is_dead(p, p->id))
				break ;
		}
	}

	// pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	// if (p->die && !p->link_b->dead_philo_detected)
	// {
	// 	p->link_b->dead_philo_detected = true;
	// 	printf("%lld %d died\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
	// }
	// pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
	return (NULL);
}
