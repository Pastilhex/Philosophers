/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/09 05:52:04 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*test(void *arg)
{
	t_philo *m = (t_philo *)arg;
	while (m->c->j < m->time_to_die)
	{
		m->c->j++;
	}
	return (m);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	mutex;
	t_philo			m;
	t_counters		c;
	int				p;
	pthread_t		*philo;

	c.i = 1;
	c.j = 0;
	m.number_of_philosophers = ft_atoi(argv[c.i++]);
	// m.time_to_die = ft_atoi(argv[c.i++]);
	// m.time_to_eat = ft_atoi(argv[c.i++]);
	// m.time_to_sleep = ft_atoi(argv[c.i++]);
	// m.number_of_times_each_philosopher_must_eat = ft_atoi(argv[c.i]);
	
	philo = (pthread_t *)malloc(m.number_of_philosophers * sizeof(pthread_t));
	
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&philo[p], NULL, &test, &m);

	pthread_join(phi)
	pthread_mutex_destroy(&mutex);
	printf("counter: %d", c.j);
}