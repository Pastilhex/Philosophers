/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/09 04:21:45 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

pthrea
int	main(int argc, char **argv)
{
	t_main		m;
	t_counters	c;

	c.i = 1;
	m.number_of_philosophers = ft_atoi(argv[c.i++]);
	m.time_to_die = ft_atoi(argv[c.i++]);
	m.time_to_eat = ft_atoi(argv[c.i++]);
	m.time_to_sleep = ft_atoi(argv[c.i++]);
	m.number_of_times_each_philosopher_must_eat = ft_atoi(argv[c.i]);

}