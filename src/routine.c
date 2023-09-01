/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/01 06:10:08 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_forks(t_philo *p)
{
	if (is_fork_one_avaiable(p, p->id) && is_fork_two_avaiable(p, p->id))
	{
		p->think = false;
		pick_own_fork(p);
		pick_next_fork(p);
		p->eat = true;
		printf("%lld %d is eating\n", (get_actual_time()
				- p->link_b->time_start), p->id + 1);
	}
}

void	check_eat(t_philo *p)
{
	if (p->eat)
	{
		p->last_meal = get_actual_time();
		usleep(p->link_b->time_to_eat * 1000);
		p->eat = false;
		p->sleep = true;
		if (!check_dead_philos(p->link_b))
			return ;
	}
}

void	check_sleep(t_philo *p)
{
	if (p->sleep)
	{
		pthread_mutex_lock(&p->fork->mutex[p->id]);
		p->fork->status[p->id] = 0;
		if (p->id == p->link_b->nbr_p - 1
			&& p->fork->status[0] == 1)
			p->fork->status[0] = 0;
		pthread_mutex_unlock(&p->fork->mutex[p->id]);
		pthread_mutex_lock(&p->fork->mutex[(p->id + 1)
			% p->link_b->nbr_p]);
		if (p->id >= 0 && p->id < p->link_b->nbr_p - 1
			&& p->fork->status[(p->id + 1) % p->link_b->nbr_p] == 1)
			p->fork->status[(p->id + 1) % p->link_b->nbr_p] = 0;
		pthread_mutex_unlock(&p->fork->mutex[(p->id + 1)
			% p->link_b->nbr_p]);
		printf("%lld %d is sleeping\n", (get_actual_time()
				- p->link_b->time_start), (p->id + 1));
		usleep(p->link_b->time_to_sleep * 1000);
		p->sleep = false;
		if (!check_dead_philos(p->link_b))
			return ;
	}	
}

void	check_think(t_philo *p)
{
	if (!p->think)
	{
		printf("%lld %d is thinking\n", (get_actual_time()
				- p->link_b->time_start), (p->id + 1));
		usleep(p->link_b->time_to_eat / 2);
		p->think = true;
		if (!check_dead_philos(p->link_b))
			return ;
	}
}

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	p->last_meal = get_actual_time();
	while (!check_dead_philos(p->link_b))
	{
		check_forks(p);
		check_eat(p);
		check_sleep(p);
		check_think(p);
		pthread_mutex_lock(&p->fork->mutex[p->id]);
		if ((get_actual_time() - p->last_meal) > p->link_b->time_to_die)
			p->die = true;
		pthread_mutex_unlock(&p->fork->mutex[p->id]);
	}
	printf("%lld %d died\n", (get_actual_time() - p->link_b->time_start), p->id + 1);
	return (NULL);
}
