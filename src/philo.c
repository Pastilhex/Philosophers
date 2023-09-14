/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/14 21:21:09 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_base			base;

	if (argc > 6)
	{
		printf("Too many arguments. Exiting...\n");
		return (1);
	}
	ft_input_args(&base, argv),
	ft_create_philos(&base);
	ft_start_threads(&base);
	ft_destroy_philos(&base);
	return (0);
}
