/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/21 23:29:01 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	start_mutex(pthread_mutex_t *m)
{
	if (pthread_mutex_init(m, NULL) != 0)
		printf("Mutex Init Fail\n");
}

void	even(t_philo *p, int i)
{
	p->left = &p->link_b->forks[i];
	p->right = &p->link_b->forks[(i + 1) % p->link_b->nbr_philos];
	p->left_f = &p->link_b->forks_f[i];
	p->right_f = &p->link_b->forks_f[(i + 1) % p->link_b->nbr_philos];
}

void	odd(t_philo *p, int i)
{
	p->left = &p->link_b->forks[(i + 1) % p->link_b->nbr_philos];
	p->right = &p->link_b->forks[i];
	p->left_f = &p->link_b->forks_f[(i + 1) % p->link_b->nbr_philos];
	p->right_f = &p->link_b->forks_f[i];
}

void	create_philos(t_base *b)
{
	int	i;

	i = 0;
	b->forks = malloc(b->nbr_philos * sizeof(pthread_mutex_t));
	b->forks_f = malloc(b->nbr_philos * sizeof(int));
	while (i < b->nbr_philos)
	{
		b->forks_f[i] = 0;
		start_mutex(&b->forks[i++]);
	}
	i = -1;
	b->philo_id = malloc(b->nbr_philos * sizeof(t_philo));
	while (++i < b->nbr_philos)
	{
		b->philo_id[i].link_b = b;
		b->philo_id[i].id = i;
		if (i % 2 != 0)
			odd(&b->philo_id[i], i);
		else
			even(&b->philo_id[i], i);
	}
	b->dead_philo_detected = false;
	b->nbr_meals_reached = false;
	start_mutex(&b->dead_philo_mutex);
	start_mutex(&b->dead_philo_mutex);
}

void	destroy_philos(t_base *b)
{
	int	i;

	i = 0;
	while (i < b->nbr_philos)
	{
		pthread_mutex_destroy(&b->forks[i++]);
	}
	pthread_mutex_destroy(&b->dead_philo_mutex);
	free(b->forks);
	free(b->forks_f);
	free(b->philo_id);
}
