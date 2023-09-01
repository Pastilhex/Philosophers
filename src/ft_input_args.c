/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/01 05:55:48 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
	b->dead_philo_detected = 0;
}
