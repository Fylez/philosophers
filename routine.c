/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:36:30 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/14 19:39:26 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		checkstop(t_table *table)
{
		int returnv;
		
		pthread_mutex_lock (&table->stop);
		returnv = table->tostop;
		pthread_mutex_unlock (&table->stop);
		return (returnv);
}
void	ft_sleep(int time)
{
	struct timeval	start_time;
	gettimeofday(&start_time, 0);
	while (get_time_elapsed(start_time) < time)
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

void	eat(t_philo *philo)
{
	if (checkstop(philo->table) == 0)
	{
		ft_print("is eating", philo);
		philo->teaten++;
		pthread_mutex_lock (&philo->leat);
		gettimeofday(&philo->last_time, 0);
		pthread_mutex_unlock (&philo->leat);
		ft_sleep(philo->table->teat);
	}

}

void	psleep(t_philo *philo)
{
	if (checkstop(philo->table) == 0)
	{
		ft_print("is sleeping", philo);
		ft_sleep(philo->table->tsleep);
	}
}

int	pickfork(t_philo *philo)
{
	int left;
	int right;

	if (philo->index == (philo->table->nphilos - 1))
	{
		left = 0;
		right = philo->table->nphilos - 1;
	}
	else
	{
		left = philo -> index;
		right = philo -> index + 1;
	}
	while (philo->table->nphilos == 1)
	{
		usleep(50);
		if(!philo->table->fork[left].__data.__lock && \
		!philo->table->fork[right].__data.__lock)
			break;
		if (checkstop(philo->table) == 1)
			return (0);
	}
	pthread_mutex_lock (&philo->table->fork[left]);
	pthread_mutex_lock (&philo->table->fork[right]);
	ft_print("has taken a fork", philo);
	ft_print("has taken a fork", philo);
	eat(philo);
	pthread_mutex_unlock (&philo->table->fork[left]);
	pthread_mutex_unlock (&philo->table->fork[right]);
}

void	*routine(void *philo)
{
	if (((t_philo *)philo)->index % 2 == 0)
		ft_sleep(((t_philo *)philo)->table->teat / 10);
	while (checkstop(((t_philo *)philo)->table) == 0)
	{
		pickfork((t_philo *)philo);
		psleep((t_philo *)philo);
		ft_print("is thinking", philo);
		if ((((t_philo *)philo)->teaten == ((t_philo *)philo)->table->aeat))
		{
			pthread_mutex_lock (&((t_philo *)philo)->table->stop);
			((t_philo *)philo)->table->pdone++;
			pthread_mutex_unlock (&((t_philo *)philo)->table->stop);
		}
	}
}

