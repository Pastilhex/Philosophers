/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/12 20:57:16 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	p->last_meal = get_actual_time();
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
	
	if ((p->id + 1) % 2 == 0)
		usleep(p->link_b->time_to_eat / 2);
	
	while (check_for_dead_philos(p) != true)
	{
		pthread_mutex_lock(&p->link_b->dead_philo_mutex);
		if (p->die == true || p->link_b->dead_philo_detected == true || check_meals(p->link_b) == true)
		{
			pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);

		if (pthread_mutex_lock(p->left) == 0)
		{
			if (p->link_b->nbr_philos > 1 && pthread_mutex_lock(p->right) == 0 && check_for_dead_philos(p) != true)
			{
				printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				
				printf("%lld %d is eating\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				pthread_mutex_lock(&p->link_b->dead_philo_mutex);
				p->meals++;
				p->last_meal = get_actual_time();
				pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
				usleep(p->link_b->time_to_eat * 1000);
				
				pthread_mutex_unlock(p->right);
				pthread_mutex_unlock(p->left);
			}
			else
				pthread_mutex_unlock(p->right);
		}
		else
			pthread_mutex_unlock(p->left);
		
		if (p->link_b->nbr_philos > 1 && check_for_dead_philos(p) != true)
		{
			printf("%lld %d is sleeping\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
			usleep(p->link_b->time_to_sleep * 1000);
		}

		if (p->link_b->nbr_philos > 1 && check_for_dead_philos(p) != true)
		{
			printf("%lld %d is thinking\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
			// usleep(60);
		}
			
	}
	return (NULL);
}
