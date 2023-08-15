/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/15 14:05:10 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*test(void *arg)
{
	t_base 	*base;
	int		i = 0;

	base = (t_base *)arg;
	while (i < 100)
	{
		i++;
		pthread_mutex_lock(&base->mutex);
		base->teste++;
		pthread_mutex_unlock(&base->mutex);
		printf("%d\n", i);
	}
	return (NULL);
}

void	ft_create_philos(t_base *base)
{
	int	i;

	i = 0;
	base->philos = (t_philo *)malloc(base->number_of_philosophers * sizeof(t_philo));
	while (i < base->number_of_philosophers)
	{
		base->philos[i].die = 0;
		base->philos[i].eat = 0;
		base->philos[i].sleep = 0;
		base->philos[i].think = 0;
		i++;
	}
}

void	ft_input_args(t_base *b, char **argv)
{
	t_counters		local;

	local.i = 1;
	local.j = 0;
	if (argv[local.i])
		b->number_of_philosophers = ft_atoi(argv[local.i++]);
	if (argv[local.i])
		b->time_to_die = ft_atoi(argv[local.i++]);
	if (argv[local.i])
		b->time_to_eat = ft_atoi(argv[local.i++]);
	if (argv[local.i])
		b->time_to_sleep = ft_atoi(argv[local.i++]);
	if (argv[local.i])
		b->nbr_of_meals = ft_atoi(argv[local.i]);
}

void	ft_start_threads(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->number_of_philosophers)
	{
		pthread_create(&base->philos[i].pt_philo, NULL, &test, &base);
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
		pthread_join(base->philos[i].pt_philo, NULL);
		printf("Finished Philo %d\n", i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_base			base;

	if (argc > 6)
	{
		printf("Too many arguments. Exiting...\n");
		return (1);
	}
	base.teste = 0;
	ft_input_args(&base, argv),
	ft_create_philos(&base);
	pthread_mutex_init(&base.mutex, NULL);
	//ft_start_threads(&base);
	int	i;

	i = 0;
	while (i < base.number_of_philosophers)
	{
		pthread_create(&base.philos[i].pt_philo, NULL, &test, &base);
		printf("Started Philo %d\n", i);
		i++;
	}
	// ft_join_threads(&base);
	i = 0;
	while (i < base.number_of_philosophers)
	{
		pthread_join(base.philos[i].pt_philo, NULL);
		printf("Finished Philo %d\n", i);
		i++;
	}
	pthread_mutex_destroy(&base.mutex);
	printf("Num: %d\n", base.teste);
}
