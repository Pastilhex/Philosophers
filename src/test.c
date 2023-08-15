/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialves-m <ialves-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:57:05 by ialves-m          #+#    #+#             */
/*   Updated: 2023/08/15 13:38:01 by ialves-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* 
void	*test(void *arg)
{
	t_base 	*base;
	int		i = 0;

	base = (t_base *)arg;
	while (i < 100000)
	{
		i++;
		pthread_mutex_lock(&base->mutex);
		base->number_of_philosophers++;
		pthread_mutex_unlock(&base->mutex);
	}
	return (NULL);
}

	
int	main(int argc, char **argv)
{
	pthread_t		philo_0;
	pthread_t		philo_1;
	t_base			base;

	base.number_of_philosophers = 0;

	pthread_mutex_init(&base.mutex, NULL);

	pthread_create(&philo_0, NULL, &test, &base);
	pthread_create(&philo_1, NULL, &test, &base);

	pthread_join(philo_0, NULL);
	pthread_join(philo_1, NULL);

	pthread_mutex_destroy(&base.mutex);

	printf("Num: %d\n", base.number_of_philosophers);
} */
