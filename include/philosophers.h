/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:40 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/07 10:10:31 by ialves-m         ###   ########.fr       */
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

typedef struct s_forks
{
	int				*status;
	pthread_mutex_t	*mutex;
}	t_forks;

typedef struct s_philo
{
	int				id;
	bool			die;
	long long		last_meal;
	bool			eat;
	bool			sleep;
	bool			think;
	struct s_base	*link_b;
	pthread_t		philo_thread;
	t_forks			*fork;
}	t_philo;

typedef struct s_base
{
	int				nbr_p;
	long long		time_start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				even_odd;
	bool			dead_philo_detected;
	pthread_mutex_t	dead_philo_mutex;
	t_philo			*philo_id;
}	t_base;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
long long	get_actual_time(void);
bool		check_dead_philos(t_base *base);
void		pick_own_fork(t_philo *philo);
void		pick_next_fork(t_philo *p);
bool		is_fork_one_avaiable(t_philo *philo, int id);
bool		is_fork_two_avaiable(t_philo *p, int id);
void		ft_create_philos(t_base *b, t_forks *f);
void		ft_input_args(t_base *b, char **argv);
void		check_forks(t_philo *p);
void		check_eat(t_philo *p);
void		check_sleep(t_philo *p);
void		check_think(t_philo *p);
void		*routine(void *arg);
void		ft_start_threads(t_base *base);
void		ft_join_threads(t_base *base);
bool		is_dead(t_philo *p);

#endif