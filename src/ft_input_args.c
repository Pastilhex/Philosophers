/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/10 12:29:33 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <limits.h>

void	ft_input_args(t_base *b, char **argv)
{
	int	i;

	i = 1;
	if (argv[i])
		b->nbr_p = ft_atoi(argv[i++]);
	if (argv[i])
		b->time_to_die = ft_atoi(argv[i++]);
	if (argv[i])
		b->time_to_eat = ft_atoi(argv[i++]);
	if (argv[i])
		b->time_to_sleep = ft_atoi(argv[i++]);
	if (argv[i])
		b->nbr_of_meals = ft_atoi(argv[i]);
	else
		b->nbr_of_meals = INT_MAX;
	b->dead_philo_detected = 0;
}
