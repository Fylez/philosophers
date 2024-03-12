/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:36:30 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/12 19:48:40 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(int time)
{
	usleep(time * 1000);
}

void	ft_print(char *reason, t_philo *philo)
{
	pthread_mutex_lock (&philo->table->stop);
	if (((t_philo *)philo)->table->tostop == 0)
	{
		printf("%ld ", get_time_elapsed(philo->table->start_time));
		printf("%d %s\n", philo->index, reason);
	}
	pthread_mutex_unlock (&philo->table->stop);

}

void	eat(t_philo *philo)
{
	ft_print("is eating", philo);
	philo->teaten++;
	pthread_mutex_lock (&philo->leat);
	gettimeofday(&philo->last_time, 0);
	pthread_mutex_unlock (&philo->leat);
	ft_sleep(philo->table->teat);
}

void	psleep(t_philo *philo)
{
	ft_print("is sleeping", philo);
	ft_sleep(philo->table->tsleep);
}

void	pickfork(t_philo *philo)
{
	ft_print("is waiting for a fork", philo);
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

	if (philo->index == (philo->table->nphilos - 1))
		pthread_mutex_unlock (&philo->table->fork[philo->index]);
	else
		pthread_mutex_unlock (&philo->table->fork[(philo->index + 1)]);
}

void *routine(void *philo)
{
	int	stop;

	stop = 0;
	if (((t_philo *)philo)->index % 2 == 0)
		ft_sleep(((t_philo *)philo)->table->teat / 10);
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
	pthread_mutex_lock (&((t_philo *)philo)->table->stop);
	((t_philo *)philo)->table->pdone++;
	pthread_mutex_unlock (&((t_philo *)philo)->table->stop);
}

