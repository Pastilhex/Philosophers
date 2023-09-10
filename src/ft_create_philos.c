/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_philos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/09 17:05:09 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	even(t_philo *p, int i)
{
	p->left = &p->link_b->forks[i];
	p->right = &p->link_b->forks[(i + 1) % p->link_b->nbr_p];
}

void	odd(t_philo *p, int i)
{
	p->left = &p->link_b->forks[(i + 1) % p->link_b->nbr_p];
	p->right = &p->link_b->forks[i];
}

void	ft_create_philos(t_base *b)
{
	int	i;

	i = 0;
	b->forks = malloc(b->nbr_p * sizeof(pthread_mutex_t));
	while (i < b->nbr_p)
	{
		pthread_mutex_init(&b->forks[i], NULL);
		i++;
	}

	i = 0;
	b->philo_id = malloc(b->nbr_p * sizeof(t_philo));
	while (i < b->nbr_p)
	{
		b->philo_id[i].link_b = b;
		b->philo_id[i].id = i;
		b->philo_id[i].die = false;
		b->philo_id[i].eat = false;
		b->philo_id[i].sleep = false;
		b->philo_id[i].think = true;
		b->philo_id[i].last_meal = b->time_start;
		b->philo_id[i].meals = 0;
		if (i % 2 == 0)
			even(&b->philo_id[i], i);
		else
			odd(&b->philo_id[i], i);
		i++;
	}

	pthread_mutex_init(&b->dead_philo_mutex, NULL);
	pthread_mutex_init(&b->meals_mutex, NULL);

}
