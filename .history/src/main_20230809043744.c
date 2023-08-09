/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/09 04:37:44 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

pthread_mutex_t	mutex;

void	test(t_main *m, int	i)
{
	while (i < m->number_of_philosophers)
	{
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_main		m;
	t_counters	c;

	pthread_mutex_init(&mutex, NULL);
	c.i = 1;
	m.number_of_philosophers = ft_atoi(argv[c.i++]);
	m.time_to_die = ft_atoi(argv[c.i++]);
	m.time_to_eat = ft_atoi(argv[c.i++]);
	m.time_to_sleep = ft_atoi(argv[c.i++]);
	m.number_of_times_each_philosopher_must_eat = ft_atoi(argv[c.i]);
	if (pthrea)
	pthread_mutex_destroy(&mutex);
}
