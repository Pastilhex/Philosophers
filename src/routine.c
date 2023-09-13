/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/13 20:45:03 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	handle_meals(t_philo *p)
{
	pthread_mutex_lock(&p->link_b->meals_mutex);
	p->meals++;
	p->last_meal = get_actual_time();
	pthread_mutex_unlock(&p->link_b->meals_mutex);
}

void	handle_eat(t_philo *p)
{
	if (pthread_mutex_lock(p->left) == 0)
	{
		if (p->link_b->nbr_philos > 1 && deads_or_meals(p) != true && pthread_mutex_lock(p->right) == 0)
		{
			printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
			printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
			handle_meals(p);
			printf("%lld %d is eating\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
			usleep(p->link_b->time_to_eat * 1000);
			pthread_mutex_unlock(p->right);
			pthread_mutex_unlock(p->left);
		}
		// else
			// pthread_mutex_unlock(p->right);
	}
	// else
		// pthread_mutex_unlock(p->left);
}

void	handle_sleep(t_philo *p)
{
	if (p->link_b->nbr_philos > 1)
	{
		printf("%lld %d is sleeping\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
		usleep(p->link_b->time_to_sleep * 1000);
	}
}

void	handle_think(t_philo *p)
{
	if (p->link_b->nbr_philos > 1)
		printf("%lld %d is thinking\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
}

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->link_b->meals_mutex);
	p->last_meal = get_actual_time();
	pthread_mutex_unlock(&p->link_b->meals_mutex);
	if ((p->id + 1) % 2 == 0)
		usleep(10);
	while (deads_or_meals(p) != true)
	{
		if (deads_or_meals(p) != true)
			handle_eat(p);
		else
			return (NULL);
		if (deads_or_meals(p) != true)
			handle_sleep(p);
		else
			return (NULL);
		if (deads_or_meals(p) != true)
			handle_think(p);
		else
			return (NULL);
	}
	return (NULL);
}
