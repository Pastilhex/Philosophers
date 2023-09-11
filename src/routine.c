/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/11 06:57:26 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*spy_routine(void *arg)
{
	t_base	*b;
	int		i;

	i = 0;
	b = arg;
	(void)b;
	while (1)
	{
		pthread_mutex_lock(&b->meals_mutex);
		while (i < b->nbr_philos)
		{
			if ((get_actual_time() - b->philo_id[i].last_meal) >= b->time_to_die)
			{
				printf("Inside\n");
			}
			i++;
		}
		pthread_mutex_unlock(&b->meals_mutex);
		i = 0;
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
		
	while (1)
	{
		// pause();
		if (pthread_mutex_lock(p->left) == 0)
		{	
			if (p->link_b->nbr_philos > 1 && pthread_mutex_lock(p->right) == 0)
			{
					
				printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				
				// pthread_mutex_lock(&p->link_b->meals_mutex);
				p->last_meal = get_actual_time();
				p->meals++;
				// pthread_mutex_unlock(&p->link_b->meals_mutex);
				
				printf("%lld %d is eating\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
				usleep(p->link_b->time_to_eat * 1000);
				pthread_mutex_unlock(p->right);
			}
			pthread_mutex_unlock(p->left);
		}

		//Only for more then 1 philo
		if (p->link_b->nbr_philos > 1)
		{
			
			printf("%lld %d is sleeping\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
			usleep(p->link_b->time_to_sleep * 1000);

			printf("%lld %d is thinking\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
			//usleep(p->link_b->time_to_eat / 2);
		}
		
		// Check if 1 only Philo died
		// if (is_dead(p) || check_dead_philos(p->link_b))
		// 	break ;
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
