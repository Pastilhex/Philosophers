/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/17 08:04:05 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	printing_eat(t_philo *p)
{
	if (p->link_b->dead_philo_detected == false)
	{
		printf("%lld %d has taken a fork\n", \
			(get_actual_time() - p->link_b->time_start), p->id + 1);
		printf("%lld %d has taken a fork\n", \
			(get_actual_time() - p->link_b->time_start), p->id + 1);
		printf("%lld %d is eating\n", \
			(get_actual_time() - p->link_b->time_start), p->id + 1);
	}
}

void	handle_eat(t_philo *p)
{
	if (p->link_b->nbr_philos > 1 && deads_or_meals(p) == false)
	{
		pthread_mutex_lock(p->left);
		pthread_mutex_lock(p->right);
		*p->left_f = 1;
		*p->right_f = 1;
		pthread_mutex_lock(&p->link_b->dead_philo_mutex);
		printing_eat(p);
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		pthread_mutex_lock(&p->link_b->meals_mutex);
		p->meals++;
		p->last_meal = get_actual_time();
		pthread_mutex_unlock(&p->link_b->meals_mutex);
		usleep(p->link_b->time_to_eat * 1000);
		*p->left_f = 0;
		*p->right_f = 0;
		pthread_mutex_unlock(p->right);
		pthread_mutex_unlock(p->left);
	}
}

void	handle_sleep(t_philo *p)
{
	if (p->link_b->nbr_philos > 1)
	{
		pthread_mutex_lock(&p->link_b->dead_philo_mutex);
		if (p->link_b->dead_philo_detected == false)
			printf("%lld %d is sleeping\n", \
				(get_actual_time() - p->link_b->time_start), (p->id + 1));
		pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		usleep(p->link_b->time_to_sleep * 1000);
	}
}

void	handle_think(t_philo *p)
{
	if (p->link_b->nbr_philos > 1)
	{
		pthread_mutex_lock(&p->link_b->dead_philo_mutex);
		if (p->link_b->dead_philo_detected == false)
		{
			printf("%lld %d is thinking\n", (get_actual_time() \
				- p->link_b->time_start), (p->id + 1));
			pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		}
		else
		{
			pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
		}
	}
	usleep(500);
}

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->link_b->meals_mutex);
	p->last_meal = get_actual_time();
	pthread_mutex_unlock(&p->link_b->meals_mutex);
	if (p->id % 2 != 0)
		usleep(p->link_b->time_to_eat / 2 * 1000);
	while (deads_or_meals(p) == false)
	{
		handle_eat(p);
		handle_sleep(p);
		handle_think(p);
	}
	return (NULL);
}
