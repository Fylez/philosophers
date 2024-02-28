/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:52:45 by lzaengel          #+#    #+#             */
/*   Updated: 2024/02/28 19:48:44 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


pickfork()
{
	pthread_mutex_lock
	say pick left fork
	
}


void routine()
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


void	init_threads(int nphilos, t_philo *philos, t_table lock)
{
	int i;
	i = 0;
	while(i <= nphilos)
	{
		philos[i].table = &lock;
		philos[i].index = i;
		pthread_create(&(philos[i].philo), NULL, test, &philos[i]);
		i++;
	}
	i = 0;
	while(i <= nphilos)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}
int	main(int argc, char *argv[])
{
	t_table lock;
	long int	nphilos;
	long int	tdie;
	long int	teat;
	long int	tsleep;
	t_philo		*philos;
	if (argc < 5 || argc > 6)
		ft_exit("Wrong numbers of arguments");
	check_args(argc, argv);
	nphilos = ft_atoi(argv[1]);
	tdie = ft_atoi(argv[2]);
	teat = ft_atoi(argv[3]);
	tsleep = ft_atoi(argv[4]);
	philos = malloc(sizeof(t_philo) * nphilos);
	pthread_mutex_init(&lock.lock, NULL);
	init_threads(nphilos, philos, lock);
}
