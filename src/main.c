/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/16 19:27:14 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->think && !philo->die)
	{
		if ()
		pthread_mutex_lock(&philo->mutex);

		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}

void	ft_create_philos(t_base *base)
{
	int	i;

	i = 1;
	base->philo_id = (t_philo *)ft_calloc(base->number_of_philosophers, sizeof(t_philo));
	while (i <= base->number_of_philosophers)
	{
		base->philo_id[i].die = 0;
		base->philo_id[i].eat = 0;
		base->philo_id[i].sleep = 0;
		base->philo_id[i].think = 1;
		i++;
	}
}

void	ft_input_args(t_base *b, char **argv)
{
	t_counters		c;

	c.i = 1;
	c.j = 1;

	// Args attribution
	if (argv[c.i])
		b->number_of_philosophers = ft_atoi(argv[c.i++]);
	if (argv[c.i])
		b->time_to_die = ft_atoi(argv[c.i++]);
	if (argv[c.i])
		b->time_to_eat = ft_atoi(argv[c.i++]);
	if (argv[c.i])
		b->time_to_sleep = ft_atoi(argv[c.i++]);
	if (argv[c.i])
		b->nbr_of_meals = ft_atoi(argv[c.i]);
	
	// Variables inicialization
	b->dead_philo_detected = 0;

	// Init Forks
	b->fork = (t_forks *)ft_calloc(b->number_of_philosophers, sizeof(t_forks));
	while (c.j <= b->number_of_philosophers)
		b->fork[c.j++] = 0;
}

void	ft_start_threads(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->number_of_philosophers)
	{
		pthread_create(&(base->philo_id[i].philo_thread), NULL, routine, &(base));
		printf("Started Philo %d\n", i);
		i++;
	}
}

void	ft_join_threads(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->number_of_philosophers)
	{
		pthread_join(base->philo_id[i].philo_thread, NULL);
		printf("Finished Philo %d\n", i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_base			base;
	t_philo			*philo;

	if (argc > 6)
	{
		printf("Too many arguments. Exiting...\n");
		return (1);
	}
	ft_input_args(&base, argv),
	ft_create_philos(&base);

//	pthread_mutex_init(&base.mutex, NULL);
//	pthread_mutex_destroy(&base.mutex);

	ft_start_threads(&base);
	ft_join_threads(&base);
}
