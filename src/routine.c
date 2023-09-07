/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/07 11:34:31 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_forks(t_philo *p)
{

		printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);

		// pthread_mutex_lock(&p->fork->mutex[p->id]);
		// pthread_mutex_lock(&p->fork->mutex[(p->id + 1) % p->link_b->nbr_p]);
		// p->fork->status[(p->id + 1) % p->link_b->nbr_p] = 1;
		// printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
		// pthread_mutex_unlock(&p->fork->mutex[(p->id + 1) % p->link_b->nbr_p]);
		// p->fork->status[p->id] = 1;
		// pthread_mutex_unlock(&p->fork->mutex[p->id]);



		// p->last_meal = get_actual_time();
		// printf("%lld %d is eating\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
		// usleep(p->link_b->time_to_eat * 1000);

		// pthread_mutex_lock(&p->fork->mutex[p->id]);
		// p->fork->status[p->id % p->link_b->nbr_p] = 0;
		// pthread_mutex_unlock(&p->fork->mutex[p->id]);

		// pthread_mutex_lock(&p->fork->mutex[(p->id + 1) % p->link_b->nbr_p]);
		// p->fork->status[(p->id + 1) % p->link_b->nbr_p] = 0;
		// pthread_mutex_unlock(&p->fork->mutex[(p->id + 1) % p->link_b->nbr_p]);

		// printf("%lld %d is sleeping\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
		// usleep(p->link_b->time_to_sleep * 1000);

		// p->think = false;

}

void	check_think(t_philo *p)
{
	if (!p->think)
	{
		printf("%lld %d is thinking\n", (get_actual_time() - p->link_b->time_start), (p->id + 1));
		//usleep(p->link_b->time_to_eat / 10);
		p->think = true;
	}
}

void	*routine(void *arg)
{
	t_philo		*p;
	int	i = 0;

	p = (t_philo *)arg;
	p->last_meal = get_actual_time();
	// if (p->id % 2 != 0)
	// 	usleep(p->link_b->time_to_eat / 2);
	while (i < 10)
	{
		check_forks(p);
		check_think(p);
		i++;
	}
	if (p->die)
		printf("%lld %d died\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
	return (NULL);
}
