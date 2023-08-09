/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/09 04:43:23 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

pthread_mutex_t	mutex;

void	test(t_main *m, int	i)
{
	while (i < m->time_to_die)
	{
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_main		m;
	t_counters	c;
	int			p;

	c.i = 1;
	m.number_of_philosophers = ft_atoi(argv[c.i++]);
	m.time_to_die = ft_atoi(argv[c.i++]);
	m.time_to_eat = ft_atoi(argv[c.i++]);
	m.time_to_sleep = ft_atoi(argv[c.i++]);
	m.number_of_times_each_philosopher_must_eat = ft_atoi(argv[c.i]);
	while (m.number_of_philosophers > p)
	{
		pthread_t	philo[p++];
	}
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&philo[p]))
	pthread_mutex_destroy(&mutex);
}
