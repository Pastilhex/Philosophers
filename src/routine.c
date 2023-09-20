/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/20 14:09:39 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	jump_off(t_philo *p)
{
	usleep(1000);
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

bool	handle_eat(t_philo *p)
{
	pthread_mutex_lock(p->left);
	pthread_mutex_lock(p->right);
	*p->left_f = 1;
	*p->right_f = 1;
	if (jump_off(p) == true)
		return (true);
	printf("%lld %d has taken a fork\n", \
		(get_actual_time() - p->link_b->time_start), p->id + 1);
	printf("%lld %d has taken a fork\n", \
		(get_actual_time() - p->link_b->time_start), p->id + 1);
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	p->meals++;
	p->last_meal = get_actual_time();
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
	printf("%lld %d is eating\n", \
		(get_actual_time() - p->link_b->time_start), p->id + 1);
	usleep(p->link_b->time_to_eat * 1000);
	*p->left_f = 0;
	*p->right_f = 0;
	pthread_mutex_unlock(p->right);
	pthread_mutex_unlock(p->left);
	if (jump_off(p) == true)
		return (true);
	return (false);
}

bool	handle_sleep(t_philo *p)
{
	printf("%lld %d is sleeping\n", \
		(get_actual_time() - p->link_b->time_start), (p->id + 1));
	usleep(p->link_b->time_to_sleep * 1000);
	if (jump_off(p) == true)
		return (true);
	return (false);
}

bool	handle_think(t_philo *p)
{
	printf("%lld %d is thinking\n", \
		(get_actual_time() - p->link_b->time_start), (p->id + 1));
	usleep(500);
	if (jump_off(p) == true)
		return (true);
	return (false);
}

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	if (p->id % 2 != 0)
		usleep(1500);
	pthread_mutex_lock(&p->link_b->dead_philo_mutex);
	p->last_meal = get_actual_time();
	pthread_mutex_unlock(&p->link_b->dead_philo_mutex);
	while (1)
	{
		if (jump_off(p) == true)
			break ;
		if (p->link_b->nbr_philos > 1)
		{
			if (handle_eat(p) == true)
				break ;
			if (handle_sleep(p) == true)
				break ;
			if (handle_think(p) == true)
				break ;
		}
	}
	return (NULL);
}
