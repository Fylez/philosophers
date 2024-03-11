/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:52:45 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/11 20:12:14 by lzaengel         ###   ########.fr       */
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

void	check_death(int nphilos, t_philo *philos)
{
	int	i;
	int	isdead;

	isdead = 0;
	while (isdead == 0)
	{
		i = 0;
		while (i < nphilos && isdead == 0)
		{
			if (get_time_elapsed(philos[i].last_time) > philos[i].table->tdie)
			{
				isdead = 1;
				ft_print("died", &philos[i]);
				pthread_mutex_lock (&philos[i].table->stop);
				philos[i].table->tostop = 1;
				pthread_mutex_unlock (&philos[i].table->stop);
			}
			i++;
		}
	}
}

void	init_threads(int nphilos, t_philo *philos, t_table *table)
{
	int	i;

	i = 0;
	gettimeofday(&table->start_time, 0);
	while (i < nphilos)
	{
		philos[i].table = table;
		philos[i].index = i;
		philos[i].teaten = 0;
		philos[i].last_time = table->start_time;
		pthread_create(&(philos[i].philo), NULL, routine, &philos[i]);
		i++;
	}
	check_death(nphilos, philos);
	i = 0;
	while (i < nphilos)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}

void	init_philos(t_table *table)
{
	int			i;
	t_philo		*philos;

	table->fork = malloc(sizeof(pthread_mutex_t) * table->nphilos);
	philos = malloc(sizeof(t_philo) * table->nphilos);
	i = 0;
	while (i < table->nphilos)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->text, NULL);
	pthread_mutex_init(&table->stop, NULL);
	init_threads(table->nphilos, philos, table);
	i = 0;
	/*while (i < table->nphilos)
	{
		free(&table->fork[i]);
		i++;
	}*/
	free(table -> fork);
	free(philos);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < 5 || argc > 6)
		ft_exit("Wrong numbers of arguments");
	check_args(argc, argv);
	if (argc == 6)
		table.aeat = ft_atoi(argv[5]);
	else
		table.aeat = -1;
	table.nphilos = ft_atoi(argv[1]);
	table.tdie = ft_atoi(argv[2]);
	table.teat = ft_atoi(argv[3]);
	table.tsleep = ft_atoi(argv[4]);
	table.tostop = 0;
	init_philos(&table);
}
