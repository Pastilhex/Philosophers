/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/10 20:39:58 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	eat(t_philo *p)
{
	if (p->id == 0)
	{
		printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
		printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
	}
	printf("%lld %d is eating\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
	
	pthread_mutex_lock(&p->link_b->meals_mutex);
	p->last_meal = get_actual_time();
	printf("Last Meal %lld\n", p->last_meal);
	p->meals++;
	pthread_mutex_unlock(&p->link_b->meals_mutex);

	usleep(p->link_b->time_to_eat * 1000);

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
		
	while (!check_dead_philos(p->link_b))
	{
		if (pthread_mutex_lock(p->left) == 0)
		{	
			if (p->link_b->nbr_p > 1 && pthread_mutex_lock(p->right) == 0)
			{
				if (is_dead(p) || check_dead_philos(p->link_b))
				{
					pthread_mutex_unlock(p->left);
					pthread_mutex_unlock(p->right);
					break ;
				}
					
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
		}

		//Only for more then 1 philo
		if (p->link_b->nbr_p > 1)
		{
			
			if (is_dead(p) || check_dead_philos(p->link_b))
				break ;
			else
			{
				printf("%lld %d is sleeping\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
				usleep(p->link_b->time_to_sleep * 1000);
			}

			if (is_dead(p) || check_dead_philos(p->link_b))
				break ;
			else
			{
				printf("%lld %d is thinking\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
				//usleep(p->link_b->time_to_eat / 2);
			}

		}
		
		// Check if 1 only Philo died
		if (is_dead(p) || check_dead_philos(p->link_b))
			break ;
	}
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	if (p->die && !p->link_b->dead_philo_detected)
	{
		p->link_b->dead_philo_detected = true;
		printf("%lld %d died\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
	}
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
	return (NULL);
}
