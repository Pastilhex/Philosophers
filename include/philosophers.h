/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:40 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/16 19:21:55 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "pthread.h"

typedef struct s_counters
{
	int	i;
	int	j;
	int	k;
}	t_counters;

typedef struct s_base
{
	int				teste;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals; //number_of_times_each_philosopher_must_eat;
	int				even_odd;
	int				philo_out;
	pthread_mutex_t	mutex;
	t_counters		*c;
}	t_base;

typedef struct s_philo
{
	pthread_t	philo_thread;
	int			die;
	int			eat;
	int			sleep;
	int			think;
	t_base		*base;
}	t_philo;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

#endif