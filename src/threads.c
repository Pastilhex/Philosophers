/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/12 15:24:26 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_start_threads(t_base *base)
{
	int	i;

	base->time_start = get_actual_time();
	i = 0;
	while (i < base->nbr_philos)
	{
		pthread_create(&(base->philo_id[i].philo_thread), NULL, routine, &(base->philo_id[i]));
		i++;
	}

	check_dead_philos(base);
	
	i = 0;
	while (i < base->nbr_philos)
	{
		pthread_join(base->philo_id[i].philo_thread, NULL);
		i++;
	}
}