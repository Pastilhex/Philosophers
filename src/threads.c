/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/11 16:13:08 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_start_threads(t_base *base)
{
	int	i;

	i = 0;
	base->time_start = get_actual_time();
	// pthread_create(&base->spy, NULL, spy_routine, &base);
	while (i < base->nbr_philos)
	{
		pthread_create(&(base->philo_id[i].philo_thread), NULL, routine, &(base->philo_id[i]));
		i++;
	}
}

void	ft_join_threads(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->nbr_philos)
	{
		pthread_join(base->philo_id[i].philo_thread, NULL);
		i++;
	}
	// pthread_join(base->spy, NULL);
}