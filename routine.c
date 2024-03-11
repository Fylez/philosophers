/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:36:30 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/11 20:14:30 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(int time)
{
	int	i;

	i = 0;
	while (i < time)
	{
		usleep(10);
		i = i + 10;
	}
}

void	ft_print(char *reason, t_philo *philo)
{
	pthread_mutex_lock (&philo->table->stop);
	if (((t_philo *)philo)->table->tostop == 0)
	{
		pthread_mutex_lock(&philo->table->text);
		printf("%ld ", get_time_elapsed(philo->table->start_time));
		printf("%d %s\n", philo->index, reason);
		pthread_mutex_unlock(&philo->table->text);
	}
	pthread_mutex_unlock (&philo->table->stop);

}

void	eat(t_philo *philo)
{
	ft_print("is eating", philo);
	philo->teaten++;
	gettimeofday(&philo->last_time, 0);
	ft_sleep(philo->table->teat);
}

void	psleep(t_philo *philo)
{
	ft_print("is sleeping", philo);
	ft_sleep(philo->table->tsleep);
}

void	pickfork(t_philo *philo)
{
	if (philo->index == (philo->table->nphilos - 1))
		pthread_mutex_lock (&philo->table->fork[0]);
	else
		pthread_mutex_lock (&philo->table->fork[philo->index]);
	ft_print("has taken a fork", philo);
	if (philo->index == (philo->table->nphilos - 1))
		pthread_mutex_lock (&philo->table->fork[philo->index]);
	else
		pthread_mutex_lock (&philo->table->fork[(philo->index + 1)]);
	ft_print("has taken a fork", philo);
	eat(philo);
	if (philo->index == (philo->table->nphilos - 1))
		pthread_mutex_unlock (&philo->table->fork[0]);
	else
		pthread_mutex_unlock (&philo->table->fork[philo->index]);
	ft_print("has put down a fork", philo);
	if (philo->index == (philo->table->nphilos - 1))
		pthread_mutex_unlock (&philo->table->fork[philo->index]);
	else
		pthread_mutex_unlock (&philo->table->fork[(philo->index + 1)]);
	ft_print("has put a down fork", philo);
}

void *routine(void *philo)
{
	int	stop;

	stop = 0;
	while ((((t_philo *)philo)->teaten
			!= ((t_philo *)philo)->table->aeat) && stop == 0)
	{
		pthread_mutex_lock (&((t_philo *)philo)->table->stop);
		if (((t_philo *)philo)->table->tostop == 1)
			stop = 1;
		pthread_mutex_unlock (&((t_philo *)philo)->table->stop);
		ft_print("is thinking", philo);
		pickfork((t_philo *)philo);
		psleep((t_philo *)philo);
	}
}

