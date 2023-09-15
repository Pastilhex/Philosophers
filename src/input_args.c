/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/15 18:14:30 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	validation_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(argv[i] && ft_is_numeric(argv[i])))
		{
			printf("Input error!\n");
			return (false);
		}
		i++;
	}
	return (true);
}

void	input_args(t_base *b, char **argv)
{
	int	i;

	i = 1;
	if (validation_args(argv) == true)
	{
		b->nbr_philos = ft_atoi(argv[i++]);
		b->time_to_die = ft_atoi(argv[i++]);
		b->time_to_eat = ft_atoi(argv[i++]);
		b->time_to_sleep = ft_atoi(argv[i++]);
		if (argv[i])
			b->nbr_meals = ft_atoi(argv[i]);
		else
			b->nbr_meals = INT_MAX;
		b->dead_philo_detected = 0;
	}
}
