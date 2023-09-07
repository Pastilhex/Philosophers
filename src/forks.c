/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/07 11:13:38 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void	pick_own_fork(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->fork->mutex[philo->id]);
// 	philo->fork->status[philo->id] = 1;
// 	pthread_mutex_unlock(&philo->fork->mutex[philo->id]);
// 	printf("%lld %d has taken a fork\n", (get_actual_time() - philo->link_b->time_start), philo->id + 1);
// }

// void	pick_next_fork(t_philo *p)
// {
// 	pthread_mutex_lock(&p->fork->mutex[(p->id + 1) % p->link_b->nbr_p]);
// 	p->fork->status[(p->id + 1) % p->link_b->nbr_p] = 1;
// 	pthread_mutex_unlock(&p->fork->mutex[(p->id + 1) % p->link_b->nbr_p]);
// 	printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
// }

bool	is_fork_one_avaiable(t_philo *p, int id)
{
	printf("PASSOU AQUI\n");
	pthread_mutex_lock(&p->fork->mutex[id]);
	if (p->fork->status[id] == 0)
	{
		p->fork->status[p->id] = 1;
		printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
		pthread_mutex_unlock(&p->fork->mutex[id]);
		return (true);
	}
	pthread_mutex_unlock(&p->fork->mutex[id]);
	return (false);
}

bool	is_fork_two_avaiable(t_philo *p, int id)
{
	pthread_mutex_lock(&p->fork->mutex[(id + 1) % p->link_b->nbr_p]);
	if (p->fork->status[(id + 1) % p->link_b->nbr_p] == 0)
	{
		p->fork->status[(p->id + 1) % p->link_b->nbr_p] = 1;
		printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
		pthread_mutex_unlock(&p->fork->mutex[(id + 1) % p->link_b->nbr_p]);
		return (true);
	}
	pthread_mutex_unlock(&p->fork->mutex[(id + 1) % p->link_b->nbr_p]);
	return (false);
}
