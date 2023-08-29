/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/29 20:12:30 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	own_fork(t_philo *philo, int stat)
{
	int	from;
	int	to;

	if (stat == 1)
	{
		from = 0;
		to = 1;
	}
	else if (stat == 0)
	{
		from = 1;
		to = 0;
	}
	if (philo->fork->status[philo->id] == from)
		philo->fork->status[philo->id] = to;
}

void	next_fork(t_philo *philo, int stat)
{
	int	from;
	int	to;

	if (stat == 1)
	{
		from = 0;
		to = 1;
	}
	else if (stat == 0)
	{
		from = 1;
		to = 0;
	}
	if (philo->id >= 0 && philo->id < (philo->link_to_base->nbr_of_philos - 1) && philo->fork->status[philo->id + 1] == from)
		philo->fork->status[philo->id + 1] = to;
	else if (philo->id == philo->link_to_base->nbr_of_philos - 1 && philo->fork->status[0] == from)
		philo->fork->status[0] = to;
}

bool	two_forks_are_avaiable(t_philo *p, int	id)
{
	int	i;
	int	fork_one;
	int	fork_two;

	i = 0;
	fork_one = 0;
	fork_two = 0;
	while (i < p->link_to_base->nbr_of_philos)
	{
		if (i == id && p->fork->status[i] == 0)
			fork_one = 1;
		if (i == id + 1 && p->fork->status[i] == 0)
			fork_two = 1;
		else if (i == p->link_to_base->nbr_of_philos && p->fork->status[0] == 0)
			fork_two = 1;
		i++;
	}
	if (fork_one && fork_two)
		return (true);
	return (false);
}

void	pick_up_forks(t_philo *p)
{
	if (p->id + 1 > 0 && p->id + 1 < p->link_to_base->nbr_of_philos && p->fork->status[p->id + 1] == 0)
	{
		p->fork->status[p->id + 1] = 1;
		p->think = false;
		pthread_mutex_unlock(&p->link_to_base->base_mutex);
		p->eat = true;
	}
	else if (p->id + 1 >= p->link_to_base->nbr_of_philos && p->fork->status[0] == 0)
	{
		p->fork->status[0] = 1;
		pthread_mutex_unlock(&p->link_to_base->base_mutex);
		p->eat = true;
	}
}

// printf("%lld Philo %d has taken a fork\n", (get_actual_time() - philo->link_to_base->time_start), philo->id + 1);
void	get_forks(t_philo *p, int	id)
{
	if (p->fork->status[id] == 0)
		p->fork->status[id] = 1;
	printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_to_base->time_start), id + 1);
	if (p->fork->status[id + 1] == 0)
			p->fork->status[id + 1] = 1;
	else if (id >= p->link_to_base->nbr_of_philos && p->fork->status[0] == 0)
		p->fork->status[0] = 1;
	printf("%lld %d has taken a fork\n", (get_actual_time() - p->link_to_base->time_start), id + 1);
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
		//if (philo->fork->status[i] == 1)
		printf("Philo %d, Fork %d with status %d\n", philo->id+1, j++, philo->fork->status[i]);
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_actual_time();
	if (philo->id % 2 != 0)
	{
		//printf("philo id:%d %% 2 = %d\n", philo->id, philo->id % 2);
		usleep(100);
	}
	while (philo->die == false)
	{
		// Pega no primeiro garfo
		pthread_mutex_lock(&philo->link_to_base->base_mutex);
		if (philo->think)
		{
			if (two_forks_are_avaiable(philo, philo->id))
				pick_up_forks(philo);
			printf("%lld %d has taken a fork\n", (get_actual_time() - philo->link_to_base->time_start), philo->id + 1);
			
			else
				pthread_mutex_unlock(&philo->link_to_base->base_mutex);
			printf("%lld %d has taken a fork\n", (get_actual_time() - philo->link_to_base->time_start), philo->id + 1);
		}
		pthread_mutex_lock(&philo->link_to_base->base_mutex);
		//print_forks(philo);
		pthread_mutex_unlock(&philo->link_to_base->base_mutex);
		
		// Começar a comer
		pthread_mutex_lock(&philo->link_to_base->base_mutex);
		if (philo->eat)
		{
			philo->last_meal = get_actual_time();
			printf("%lld %d is eating\n", (get_actual_time() - philo->link_to_base->time_start), philo->id + 1);
			usleep(philo->link_to_base->time_to_eat * 1000);
			philo->eat = false;
			philo->sleep = true;
			pthread_mutex_unlock(&philo->link_to_base->base_mutex);
		}
		else
			pthread_mutex_unlock(&philo->link_to_base->base_mutex);

		// Começa a dormir
		pthread_mutex_lock(&philo->link_to_base->base_mutex);
		if (philo->sleep)
		{
			philo->fork->status[philo->id] = 0;
			if (philo->id + 1 == philo->link_to_base->nbr_of_philos && philo->fork->status[0] == 1)
				philo->fork->status[0] = 0;
			else if (philo->id + 1 < philo->link_to_base->nbr_of_philos && philo->fork->status[philo->id + 1] == 1)
				philo->fork->status[philo->id + 1] = 0;	
			pthread_mutex_unlock(&philo->link_to_base->base_mutex);
			printf("%lld %d is sleeping\n", (get_actual_time() - philo->link_to_base->time_start), philo->id + 1);
			usleep(philo->link_to_base->time_to_sleep * 1000);
			philo->sleep = false;
			philo->think = true;
		}
		else
			pthread_mutex_unlock(&philo->link_to_base->base_mutex);
		
		
		if (philo->think)
		{
			printf("%lld %d is thinking\n", (get_actual_time() - philo->link_to_base->time_start), philo->id + 1);
			usleep(100);
		}


		pthread_mutex_lock(&philo->mutex);
		if ((get_actual_time() - philo->last_meal) > philo->link_to_base->time_to_die)
			philo->die = true;
		pthread_mutex_unlock(&philo->mutex);
	}
	printf("%lld %d died. Last meal: %lld, Time to die: %d\n", (get_actual_time() - philo->link_to_base->time_start), philo->id + 1, philo->last_meal, philo->link_to_base->time_to_die);
	return (NULL);
}

void	ft_create_philos(t_base *b, t_forks *f)
{
	int	i;

	i = 0;
	pthread_mutex_init(&b->base_mutex, NULL);
	b->philo_id = (t_philo *)ft_calloc(b->nbr_of_philos, sizeof(t_philo));
	while (i < b->nbr_of_philos)
	{
		b->philo_id[i].fork = f;
		b->philo_id[i].link_to_base = b;
		pthread_mutex_init(&b->philo_id[i].mutex, NULL);
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
	while (i < b->nbr_of_philos)
	{
		f->status[i] = 0;
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
		pthread_mutex_destroy(&base.philo_id[i++].mutex);
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
