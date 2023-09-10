/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/09/09 17:07:18 by ialves-m         ###   ########.fr       */
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
	ft_join_threads(&base);
}

	// • Any state change of a philosopher must be formatted as follows:
	// 	◦ timestamp_in_ms X has taken a fork
	// 	◦ timestamp_in_ms X is eating
	// 	◦ timestamp_in_ms X is sleeping
	// 	◦ timestamp_in_ms X is thinking
	// 	◦ timestamp_in_ms X died
	//	5 / 300 / 100 / 100
	//	nbr_p
	//	time_to_die
	//	time_to_eat
	//	time_to_sleep
	//	[number_of_times_each_philosopher_must_eat]
