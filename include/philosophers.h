/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:40 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/17 06:02:00 by ialves-m         ###   ########.fr       */
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
# include <limits.h>

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				meals;
	int				*left_f;
	int				*right_f;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		philo_thread;
	struct s_base	*link_b;
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
	int				*forks_f;
	pthread_t		spy;
	pthread_mutex_t	dead_philo_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo_id;
}	t_base;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
bool		ft_is_numeric(char *str);
long long	get_actual_time(void);
void		create_philos(t_base *b);
void		destroy_philos(t_base *b);
void		input_args(t_base *b, char **argv);
void		even(t_philo *p, int i);
void		odd(t_philo *p, int i);
void		*routine(void *arg);
void		start_threads(t_base *base);
long long	last_meal_time(t_philo *p);
bool		check_meals(t_base *b);
void		handle_eat(t_philo *p);
void		handle_sleep(t_philo *p);
void		handle_think(t_philo *p);
bool		deads_or_meals(t_philo *p);
void		check_dead_philos(t_base *b);
long long	what_time(long long current, long long last_meal);

#endif