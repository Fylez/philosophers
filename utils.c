/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:37:38 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/22 16:37:27 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_elapsed(struct timeval p_time)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, 0);
	time = (current_time.tv_sec - p_time.tv_sec) * 1000;
	time = time + ((current_time.tv_usec - p_time.tv_usec) / 1000);
	return (time);
}

int	checkstop(t_table *table)
{
	int	returnv;

	pthread_mutex_lock (&table->stop);
	returnv = table->tostop;
	pthread_mutex_unlock (&table->stop);
	return (returnv);
}

void	ft_sleep( t_table *table, int time)
{
	long	start_time;
	start_time = get_time_elapsed(table->start_time);
	while (get_time_elapsed(table->start_time) - start_time < time)
		usleep(50);
}

void	ft_print(char *reason, t_philo *philo)
{
	pthread_mutex_lock (&philo->table->text);
	if (checkstop(((t_philo *)philo)->table) == 0)
	{
		printf("%ld ", get_time_elapsed(philo->table->start_time));
		printf("%d %s\n", philo->index, reason);
	}
	pthread_mutex_unlock (&philo->table->text);
}

void	ft_print_death(t_philo *philo)
{
	pthread_mutex_lock (&philo->table->text);
	printf("%ld ", get_time_elapsed(philo->table->start_time));
	printf("%d died\n", philo->index);
	pthread_mutex_unlock (&philo->table->text);
}
