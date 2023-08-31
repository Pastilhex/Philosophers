/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/31 17:43:32 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	pick_own_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork->mutex[philo->id]);
	if (philo->fork->status[philo->id] == 0)
		philo->fork->status[philo->id] = 1;
	printf("%lld %d has taken a fork\n", (get_actual_time() - philo->link_to_base->time_start), philo->id + 1);
	pthread_mutex_unlock(&philo->fork->mutex[philo->id]);
}

void	pick_next_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork->mutex[(philo->id + 1) % philo->link_to_base->nbr_of_philos]);
	if (philo->id < philo->link_to_base->nbr_of_philos - 1 && philo->fork->status[(philo->id + 1) % philo->link_to_base->nbr_of_philos] == 0)
		philo->fork->status[(philo->id + 1) % philo->link_to_base->nbr_of_philos] = 1;
	pthread_mutex_unlock(&philo->fork->mutex[(philo->id + 1) % philo->link_to_base->nbr_of_philos]);
	printf("%lld %d has taken a fork\n", (get_actual_time() - philo->link_to_base->time_start), philo->id + 1);
}

bool	is_fork_one_avaiable(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->fork->mutex[id]);
	if (philo->fork->status[id] == 0)
	{	
		pthread_mutex_unlock(&philo->fork->mutex[id]);
		return (true);
	}
	pthread_mutex_unlock(&philo->fork->mutex[id]);
	return (false);
}

bool	is_fork_two_avaiable(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->fork->mutex[(id + 1) % philo->link_to_base->nbr_of_philos]);
	if (philo->fork->status[(id + 1) % philo->link_to_base->nbr_of_philos] == 0)
	{
		pthread_mutex_unlock(&philo->fork->mutex[(id + 1) % philo->link_to_base->nbr_of_philos]);
		return (true);
	}
	pthread_mutex_unlock(&philo->fork->mutex[(id + 1) % philo->link_to_base->nbr_of_philos]);
	return (false);
}

void	print_forks(t_philo *philo)
{
	(void) philo;
	int	i;
	int	j;
	
	i = 0;
	j = 1;
	while (i < philo->link_to_base->nbr_of_philos)
	{
		printf("Philo %d, Fork %d with status %d\n", philo->id+1, j++, philo->fork->status[i]);
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_actual_time();
	while (philo->die == false)
	{
		if (is_fork_one_avaiable(philo, philo->id) && is_fork_two_avaiable(philo, philo->id))
		{
			philo->think = false;
			pick_own_fork(philo);
			pick_next_fork(philo);
			philo->eat = true;
			printf("%lld %d is eating\n", (get_actual_time() - philo->link_to_base->time_start), philo->id + 1);
		}
		
		if (philo->eat)
		{
			philo->last_meal = get_actual_time();
			usleep(philo->link_to_base->time_to_eat * 1000);
			philo->eat = false;
			philo->sleep = true;
		}
		
		if (philo->sleep)
		{
			pthread_mutex_lock(&philo->fork->mutex[philo->id]);
			philo->fork->status[philo->id] = 0;
			if (philo->id == philo->link_to_base->nbr_of_philos - 1 && philo->fork->status[0] == 1)
				philo->fork->status[0] = 0;
			pthread_mutex_unlock(&philo->fork->mutex[philo->id]);

			pthread_mutex_lock(&philo->fork->mutex[(philo->id + 1) % philo->link_to_base->nbr_of_philos]);
			if (philo->id >= 0 && philo->id < philo->link_to_base->nbr_of_philos -1 && philo->fork->status[(philo->id + 1) % philo->link_to_base->nbr_of_philos] == 1)
				philo->fork->status[(philo->id + 1) % philo->link_to_base->nbr_of_philos] = 0;
			pthread_mutex_unlock(&philo->fork->mutex[(philo->id + 1) % philo->link_to_base->nbr_of_philos]);
			
			printf("%lld %d is sleeping\n", (get_actual_time() - philo->link_to_base->time_start), (philo->id + 1));
			usleep(philo->link_to_base->time_to_sleep * 1000);
			philo->sleep = false;
		}		
		
		if (!philo->think)
		{
			printf("%lld %d is thinking\n", (get_actual_time() - philo->link_to_base->time_start), (philo->id + 1) );
			usleep(philo->link_to_base->time_to_eat / 2);
			philo->think = true;
		}
		
		pthread_mutex_lock(&philo->fork->mutex[philo->id]);
		if ((get_actual_time() - philo->last_meal) > philo->link_to_base->time_to_die)
			philo->die = true;
		pthread_mutex_unlock(&philo->fork->mutex[philo->id]);
	}
	printf("%lld %d died\n", (get_actual_time() - philo->link_to_base->time_start), philo->id);
	return (NULL);
}

void	ft_create_philos(t_base *b, t_forks *f)
{
	int	i;

	i = 0;
	b->philo_id = (t_philo *)ft_calloc(b->nbr_of_philos, sizeof(t_philo));
	while (i < b->nbr_of_philos)
	{
		b->philo_id[i].fork = f;
		b->philo_id[i].link_to_base = b;
		b->philo_id[i].id = i;
		b->philo_id[i].die = false;
		b->philo_id[i].eat = false;
		b->philo_id[i].sleep = false;
		b->philo_id[i].think = true;
		b->philo_id[i].last_meal = b->time_start;
		i++;
	}
	i = 0;
	f->status = (int *)ft_calloc(b->nbr_of_philos, sizeof(int));
	f->mutex = (pthread_mutex_t *)ft_calloc(b->nbr_of_philos, sizeof(pthread_mutex_t));
	while (i < b->nbr_of_philos)
	{
		f->status[i] = 0;
		pthread_mutex_init(&f->mutex[i], NULL);
		i++;
	}		
}

void	ft_input_args(t_base *b, char **argv)
{
	int	i;

	i = 1;
	if (argv[i])
		b->nbr_of_philos = ft_atoi(argv[i++]);
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
	while (i < base->nbr_of_philos)
	{
		pthread_create(&(base->philo_id[i].philo_thread), NULL, routine, &(base->philo_id[i]));
		i++;
	}
}

void	ft_join_threads(t_base *base)
{
	int	i;

	i = 0;
	while (i < base->nbr_of_philos)
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
	base.time_start = get_actual_time();

	ft_input_args(&base, argv),
	ft_create_philos(&base, &fork);
	ft_start_threads(&base);
	ft_join_threads(&base);

	while (i < base.nbr_of_philos)
		pthread_mutex_destroy(&fork.mutex[i++]);
}

	// • Any state change of a philosopher must be formatted as follows:
	// 	◦ timestamp_in_ms X has taken a fork
	// 	◦ timestamp_in_ms X is eating
	// 	◦ timestamp_in_ms X is sleeping
	// 	◦ timestamp_in_ms X is thinking
	// 	◦ timestamp_in_ms X died
	//	5 / 300 / 100 / 100
	//	nbr_of_philos
	//	time_to_die
	//	time_to_eat
	//	time_to_sleep
	//	[number_of_times_each_philosopher_must_eat]
