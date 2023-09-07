/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_philos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/07 11:07:46 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	check_mutex_init(pthread_mutex_t *mutex)
{
	int	result;
	result = pthread_mutex_init(mutex, NULL);
	if (result > 0)
		printf("Mutex init fail\n");
}

void	ft_create_philos(t_base *b, t_forks *f)
{
	int	i;

	i = 0;
	b->philo_id = (t_philo *)ft_calloc(b->nbr_p, sizeof(t_philo));
	while (i < b->nbr_p)
	{
		b->philo_id[i].fork = f;
		b->philo_id[i].link_b = b;
		b->philo_id[i].id = i;
		b->philo_id[i].die = false;
		b->philo_id[i].eat = false;
		b->philo_id[i].sleep = false;
		b->philo_id[i].think = true;
		b->philo_id[i].last_meal = b->time_start;
		i++;
	}

	
	i = 0;
	f->status = (int *)ft_calloc(b->nbr_p, sizeof(int));
	f->mutex = (pthread_mutex_t *)ft_calloc(b->nbr_p, sizeof(pthread_mutex_t));
	while (i < b->nbr_p)
	{
		f->status[i] = 0;
		//pthread_mutex_init(&f->mutex[i], NULL);
		check_mutex_init(&f->mutex[i]);
		i++;
	}
	pthread_mutex_init(&b->dead_philo_mutex, NULL);
}
