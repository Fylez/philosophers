/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:36:30 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/22 16:49:51 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	think(t_philo *philo)
{
	ft_print("is thinking", philo);
	ft_sleep(philo->table, 1);
}

void	eat(t_philo *philo)
{
	if (checkstop(philo->table) == 0)
	{
		ft_print("is eating", philo);
		philo->teaten++;
		pthread_mutex_lock (&philo->table->stop);
		gettimeofday(&philo->last_time, 0);
		pthread_mutex_unlock (&philo->table->stop);
		ft_sleep(philo->table, philo->table->teat);
	}
}

void	psleep(t_philo *philo)
{
	if (checkstop(philo->table) == 0)
	{
		ft_print("is sleeping", philo);
		ft_sleep(philo->table, philo->table->tsleep);
	}
}

void	pickfork(t_philo *philo, int left, int right)
{
	if (philo->table->nphilos == 1)
	{
		ft_print("has taken a fork", philo);
		ft_sleep(philo->table, philo->table->tdie);
		return ;
	}
	pthread_mutex_lock (&philo->table->fork[left]);
	ft_print("has taken a fork", philo);
	pthread_mutex_lock (&philo->table->fork[right]);
	ft_print("has taken a fork", philo);
	eat(philo);
	pthread_mutex_unlock (&philo->table->fork[left]);
	pthread_mutex_unlock (&philo->table->fork[right]);
}

void	*routine(void *philo)
{
	int	left;
	int	right;

	left = ((t_philo *)philo)->index;
	right = ((t_philo *)philo)->index + 1;
	if (((t_philo *)philo)->index == ((t_philo *)philo)->table->nphilos - 1)
		right = 0;
	if (((t_philo *)philo)->index % 2 == 0)
		ft_sleep(((t_philo *)philo)->table,
			((t_philo *)philo)->table->teat / 10);
	while (checkstop(((t_philo *)philo)->table) == 0)
	{
		pickfork((t_philo *)philo, left, right);
		psleep((t_philo *)philo);
		think((t_philo *)philo);
		if ((((t_philo *)philo)->teaten == ((t_philo *)philo)->table->aeat))
		{
			pthread_mutex_lock (&((t_philo *)philo)->table->stop);
			((t_philo *)philo)->table->pdone++;
			pthread_mutex_unlock (&((t_philo *)philo)->table->stop);
		}
	}
	return (0);
}
