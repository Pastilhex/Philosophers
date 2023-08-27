/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:40 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/27 16:54:22 by ialves-m         ###   ########.fr       */
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
}	t_forks;

typedef struct s_philo
{
	int				id;
	bool			die;
	bool			eat;
	bool			sleep;
	bool			think;
	struct s_base	*link_to_base;
	pthread_t		philo_thread;
	pthread_mutex_t	mutex;
	t_forks			*fork;
}	t_philo;

typedef struct s_base
{
	int				number_of_philosophers;
	long long		time_start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				even_odd;
	int				dead_philo_detected;
	pthread_mutex_t	base_mutex;
	t_philo			*philo_id;
}	t_base;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
long long	get_actual_time(void);

#endif