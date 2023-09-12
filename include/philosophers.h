/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:40 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/12 06:49:59 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "pthread.h"
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				id;
	bool			die;
	long long		last_meal;
	int				meals;
	bool			eat;
	bool			sleep;
	bool			think;
	pthread_t		philo_thread;
	struct s_base	*link_b;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

typedef struct s_base
{
	long long		time_start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_philos;
	int				nbr_meals;
	bool			dead_philo_detected;
	bool			nbr_meals_reached;
	pthread_t		spy;
	pthread_mutex_t	dead_philo_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo_id;
}	t_base;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
long long	get_actual_time(void);
void		check_dead_philos(t_base *base);
void		ft_create_philos(t_base *b);
void		ft_destroy_philos(t_base *b);
void		ft_input_args(t_base *b, char **argv);
void		even(t_philo *p, int i);
void		odd(t_philo *p, int i);
void		*routine(void *arg);
void		*spy_routine(void *arg);
void		ft_start_threads(t_base *base);
void		ft_join_threads(t_base *base);
bool		is_dead(t_base *b, int i);
long long	last_meal_time(t_philo *p);
bool		check_meals(t_base *b);
bool		check_dead_meals(t_philo *p);
bool	check_for_dead_philos(t_philo *p);

#endif