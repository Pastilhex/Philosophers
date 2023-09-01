/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/01 05:45:53 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	pick_own_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork->mutex[philo->id]);
	if (philo->fork->status[philo->id] == 0)
		philo->fork->status[philo->id] = 1;
	printf("%lld %d has taken a fork\n", (get_actual_time()
			- philo->link_b->time_start), philo->id + 1);
	pthread_mutex_unlock(&philo->fork->mutex[philo->id]);
}

void	pick_next_fork(t_philo *p)
{
	pthread_mutex_lock(&p->fork->mutex[(p->id + 1)
		% p->link_b->nbr_p]);
	if (p->id < p->link_b->nbr_p - 1
		&& p->fork->status[(p->id + 1) % p->link_b->nbr_p] == 0)
		p->fork->status[(p->id + 1) % p->link_b->nbr_p] = 1;
	pthread_mutex_unlock(&p->fork->mutex[(p->id + 1)
		% p->link_b->nbr_p]);
	printf("%lld %d has taken a fork\n", (get_actual_time()
			- p->link_b->time_start), p->id + 1);
}

bool	is_fork_one_avaiable(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->fork->mutex[id]);
	if (philo->fork->status[id] == 0)
	{	
		pthread_mutex_unlock(&philo->fork->mutex[id]);
		return (true);
	}
	pthread_mutex_unlock(&philo->fork->mutex[id]);
	return (false);
}

bool	is_fork_two_avaiable(t_philo *p, int id)
{
	pthread_mutex_lock(&p->fork->mutex[(id + 1)
		% p->link_b->nbr_p]);
	if (p->fork->status[(id + 1) % p->link_b->nbr_p] == 0)
	{
		pthread_mutex_unlock(&p->fork->mutex[(id + 1)
			% p->link_b->nbr_p]);
		return (true);
	}
	pthread_mutex_unlock(&p->fork->mutex[(id + 1)
		% p->link_b->nbr_p]);
	return (false);
}
