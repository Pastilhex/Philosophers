/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/07 09:52:48 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	is_dead(t_philo *p)
{
	pthread_mutex_lock(&p->fork->mutex[p->id]);
	if ((get_actual_time() - p->last_meal) > p->link_b->time_to_die)
	{
		p->link_b->dead_philo_detected = true;
		pthread_mutex_unlock(&p->fork->mutex[p->id]);
		return (true);
	}
	pthread_mutex_unlock(&p->fork->mutex[p->id]);
	return (false);
}

bool	check_dead_philos(t_base *base)
{
	pthread_mutex_lock(&base->dead_philo_mutex);
	if (base->dead_philo_detected)
	{
		pthread_mutex_unlock(&base->dead_philo_mutex);
		return (true);
	}
	pthread_mutex_unlock(&base->dead_philo_mutex);
	return (false);
}
