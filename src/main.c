/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/25 13:01:09 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	actual_time(void)
{
	long long			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

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
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->die == 0)
	{
		pthread_mutex_lock(&philo->b_mutex->base_mutex);
		if (forks_are_avaiable(philo, philo->id))
		{

			philo->fork->status[philo->id] = 1;
			printf("Fork %d Status %d\n", philo->id, philo->fork->status[philo->id]);
			philo->fork->status[philo->id] = 0;

			philo->fork->status[philo->id + 1] = 1;
			printf("Fork %d Status %d\n", philo->id + 1, philo->fork->status[philo->id + 1]);
			philo->fork->status[philo->id + 1] = 0;

			printf("Philo %d has taken a fork\n", philo->id + 1);
			pthread_mutex_unlock(&philo->b_mutex->base_mutex);

			break;
		}	
		else
			pthread_mutex_unlock(&philo->b_mutex->base_mutex);

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
			
	}
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
		b->philo_id[i].b_mutex = b;
		pthread_mutex_init(&b->philo_id[i].mutex, NULL);
		b->philo_id[i].id = i;
		b->philo_id[i].die = 0;
		b->philo_id[i].eat = 0;
		b->philo_id[i].sleep = 0;
		b->philo_id[i].think = 0;
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
		printf("Created Philo %d\n", base->philo_id[i].id + 1);
		usleep(1000);
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
		printf("Finished Philo %d\n", i + 1);
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
	//actual_time();
	ft_input_args(&base, argv),
	ft_create_philos(&base, &fork);

	ft_start_threads(&base);
	ft_join_threads(&base);

	while (i < base.number_of_philosophers)
		pthread_mutex_destroy(&base.philo_id[i++].mutex);
}

