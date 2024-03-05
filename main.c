/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:52:45 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/05 18:45:23 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_threads(int nphilos, t_philo *philos, t_table table)
{
	int	i;

	i = 0;
	while (i <= nphilos)
	{
		philos[i].table = &table;
		philos[i].index = i;
		pthread_create(&(philos[i].philo), NULL, routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i <= nphilos)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}

void	init_table(long int nphilos)
{
	t_table		table;
	t_philo		*philos;
	int			i;

	i = 0;
	philos = malloc(sizeof(t_philo) * nphilos);
	table.fork = malloc(sizeof(pthread_mutex_t) * nphilos);
	while (i < nphilos)
	{
		pthread_mutex_init(&table.fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&table.text, NULL);
	init_threads(nphilos, philos, table);
}

int	main(int argc, char *argv[])
{
	long int	nphilos;
	long int	tdie;
	long int	teat;
	long int	tsleep;

	if (argc < 5 || argc > 6)
		ft_exit("Wrong numbers of arguments");
	check_args(argc, argv);
	nphilos = ft_atoi(argv[1]);
	tdie = ft_atoi(argv[2]);
	teat = ft_atoi(argv[3]);
	tsleep = ft_atoi(argv[4]);
	init_table(nphilos);
}
