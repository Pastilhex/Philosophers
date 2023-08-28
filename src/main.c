/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/28 16:14:32 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	forks_are_avaiable(t_philo *p, int	id)
{
	if (p->fork->status[id] == 0
		&& ((p->fork->status[id + 1] && p->fork->status[id + 1] == 0)
		|| (!p->fork->status[id + 1] && p->fork->status[0] == 0)))
		return (true);
	return (false);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	long long 	time_to_die;
	long long 	get_time;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_actual_time();
	pthread_mutex_unlock(&philo->mutex);
	while (philo->die == false)
	{
		pthread_mutex_lock(&philo->link_to_base->base_mutex);
		if (forks_are_avaiable(philo, philo->id) && (philo->sleep == false))
		{
			// Passa do estado "a pensar" para o estado "a comer"
			philo->think = false;
			
			// Pega um garfo
			philo->fork->status[philo->id] = 1;
			printf("%lld %d has taken a fork\n", get_actual_time(), philo->id + 1);
			
			// Pega outro garfo
			philo->fork->status[philo->id + 1] = 1;
			printf("%lld %d has taken a fork\n", get_actual_time(), philo->id + 1);
			
			pthread_mutex_unlock(&philo->link_to_base->base_mutex);
			
			
			// Comeca a comer
			philo->eat = true;
			philo->last_meal = get_actual_time();
			
			printf("%lld %d is eating\n", get_actual_time(), philo->id + 1);
			usleep(philo->link_to_base->time_to_eat * 1000);
			
			// Depois de comer comeca a dormir
			pthread_mutex_lock(&philo->link_to_base->base_mutex);
			philo->fork->status[philo->id] = 0;
			philo->fork->status[philo->id + 1] = 0;
			philo->eat = false;
			philo->sleep = true;
			pthread_mutex_unlock(&philo->link_to_base->base_mutex);
		}	
		
		else if (philo->sleep == true)
		{
			pthread_mutex_unlock(&philo->link_to_base->base_mutex);

			// Está a dormir
			printf("%lld %d is sleeping\n", get_actual_time(), philo->id + 1);
			usleep(philo->link_to_base->time_to_sleep * 1000);
			
			philo->sleep = false;
			philo->think = true;
			printf("%lld %d is thinking\n", get_actual_time(), philo->id + 1);
		}
		else
			pthread_mutex_unlock(&philo->link_to_base->base_mutex);

		usleep(100);
	
		pthread_mutex_lock(&philo->mutex);
		
		get_time = get_actual_time();
		time_to_die = get_time - philo->last_meal;
		// printf("get time %lld\n", get_time);
		// printf("last meal %lld\n", philo->last_meal);
		// printf("time to die %lld\n", time_to_die);

		if (time_to_die > philo->link_to_base->time_to_die)
		{
			printf("Philo %d Time to die: %lld\n", philo->id, time_to_die);
			philo->die = true;
		}
		pthread_mutex_unlock(&philo->mutex);
	}
	printf("%lld %d died\n", get_actual_time(), philo->id + 1);
	return (NULL);
}

void	ft_create_philos(t_base *b, t_forks *f)
{
	int	i;

	i = 0;
	pthread_mutex_init(&b->base_mutex, NULL);
	b->philo_id = (t_philo *)ft_calloc(b->number_of_philosophers, sizeof(t_philo));
	while (i < b->number_of_philosophers)
	{
		b->philo_id[i].fork = f;
		b->philo_id[i].link_to_base = b;
		pthread_mutex_init(&b->philo_id[i].mutex, NULL);
		b->philo_id[i].id = i;
		b->philo_id[i].die = false;
		b->philo_id[i].eat = false;
		b->philo_id[i].sleep = false;
		b->philo_id[i].think = false;
		i++;
	}
	i = 0;
	f->status = (int *)ft_calloc(b->number_of_philosophers, sizeof(int));
	while (i < b->number_of_philosophers)
		f->status[i++] = 0;	
}

void	ft_input_args(t_base *b, char **argv)
{
	int	i;

	i = 1;
	if (argv[i])
		b->number_of_philosophers = ft_atoi(argv[i++]);
	if (argv[i])
		b->time_to_die = ft_atoi(argv[i++]);
	if (argv[i])
		b->time_to_eat = ft_atoi(argv[i++]);
	if (argv[i])
		b->time_to_sleep = ft_atoi(argv[i++]);
	if (argv[i])
		b->nbr_of_meals = ft_atoi(argv[i]);
	b->dead_philo_detected = 0;
}

void	ft_start_threads(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->number_of_philosophers)
	{
		pthread_create(&(base->philo_id[i].philo_thread), NULL, routine, &(base->philo_id[i]));
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
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_base			base;
	t_forks			fork;
	int	i = 0;

	if (argc > 6)
	{
		printf("Too many arguments. Exiting...\n");
		return (1);
	}
	ft_input_args(&base, argv),
	ft_create_philos(&base, &fork);

	ft_start_threads(&base);
	ft_join_threads(&base);

	while (i < base.number_of_philosophers)
		pthread_mutex_destroy(&base.philo_id[i++].mutex);
}

	// • Any state change of a philosopher must be formatted as follows:
	// 	◦ timestamp_in_ms X has taken a fork
	// 	◦ timestamp_in_ms X is eating
	// 	◦ timestamp_in_ms X is sleeping
	// 	◦ timestamp_in_ms X is thinking
	// 	◦ timestamp_in_ms X died
	//	5 / 300 / 100 / 100
	//	number_of_philosophers
	//	time_to_die
	//	time_to_eat
	//	time_to_sleep
	//	[number_of_times_each_philosopher_must_eat]
