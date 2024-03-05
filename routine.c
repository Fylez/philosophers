/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:36:30 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/05 19:06:01 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

eat(t_philo philo)
{
	pthread_mutex_lock(&table.text);
	printf("")
	pthread_mutex_unlock(&table.text);
}

think(t_philo philo)
{
	pthread_mutex_lock(&table.text);
	pthread_mutex_unlock(&table.text);
}

pickfork(t_philo philo)
{
	pthread_mutex_lock fork;
	pthread_mutex_lock(&table.text);
	say pick left fork
	pthread_mutex_unlock(&table.text);
	unlock fork
}

void routine(t_philo philo)
{
	while(!finish)
	{
		think
		pickfork
		eat and reset timer
		sleep
	}
}

void	*test(void *philo)
{
	pthread_mutex_lock(&((t_philo *)philo)->table->lock);
	printf("%d\n",((t_philo *)philo)->index);
	printf("test\n");
	printf("test2\n");
	printf("test3\n");
	pthread_mutex_unlock(&((t_philo *)philo)->table->lock);
}