/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/15 18:17:31 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	start_threads(t_base *base)
{
	int	i;

	base->time_start = get_actual_time();
	i = 0;
	while (i < base->nbr_philos)
	{
		base->philo_id[i].last_meal = base->time_start;
		pthread_create(&(base->philo_id[i].philo_thread), \
			NULL, routine, &(base->philo_id[i]));
		i++;
		usleep(100);
	}
	check_dead_philos(base);
	i = 0;
	while (i < base->nbr_philos)
		pthread_join(base->philo_id[i++].philo_thread, NULL);
}
