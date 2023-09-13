/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/13 14:53:13 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	handle_meals(t_philo *p)
{
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	p->meals++;
	p->last_meal = get_actual_time();
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
}

void	handle_eat(t_philo *p)
{
	if (pthread_mutex_lock(p->left) == 0)
	{
		if (p->link_b->nbr_philos > 1 && p->link_b->dead_philo_detected == true && pthread_mutex_lock(p->right) == 0 && check_deads_or_meals(p) != true)
		{
			printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
			printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
			handle_meals(p);
			printf("%lld %d is eating\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
			usleep(p->link_b->time_to_eat * 1000);
			pthread_mutex_unlock(p->right);
			pthread_mutex_unlock(p->left);
		}
		else
			pthread_mutex_unlock(p->right);
	}
	else
		pthread_mutex_unlock(p->left);
}

void	handle_sleep(t_philo *p)
{
	if (p->link_b->nbr_philos > 1 && p->link_b->dead_philo_detected == true && check_deads_or_meals(p) != true)
	{
		printf("%lld %d is sleeping\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
		usleep(p->link_b->time_to_sleep * 1000);
	}
}

void	handle_think(t_philo *p)
{
	if (p->link_b->nbr_philos > 1 && p->link_b->dead_philo_detected == true && check_deads_or_meals(p) != true)
		printf("%lld %d is thinking\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
}

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	p->last_meal = get_actual_time();
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
	
	if ((p->id + 1) % 2 == 0)
		usleep(p->link_b->time_to_eat / 2);
	

	printf("p->link_b->dead_philo_detected %d\n", p->link_b->dead_philo_detected);
	printf("p->link_b->nbr_meals_reached %d\n", p->link_b->nbr_meals_reached);
	
	while (1)
	{
		pthread_mutex_lock(&p->link_b->dead_philo_mutex);
		if (p->link_b->dead_philo_detected != true)
		{
			pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		
		pthread_mutex_lock(&p->link_b->dead_philo_mutex);
		if (p->link_b->nbr_meals_reached != true)
		{
			pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		
		handle_eat(p);
		handle_sleep(p);
		handle_think(p);
	}
	return (NULL);
}
