/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:40 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/03 11:10:20 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

typedef struct s_counters
{
	int	i;
	int	j;
	int	k;
}	t_counters;

typedef struct s_main
{
	int	n_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int n_of_times_each_philo_must_eat;
}	t_main;

#endif