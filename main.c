/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:52:45 by lzaengel          #+#    #+#             */
/*   Updated: 2024/02/27 17:23:45 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	*test()
{
	printf("test\n");
	printf("test2\n");
	printf("test3\n");
}
void	init_threads(int nphilos, pthread_t *philos)
{
	int i;
	pthread_mutex
	i = 0;
	while(i <= nphilos)
	{
		pthread_create(&philos[i], NULL, test, NULL);
		i++;
	}
}
int	main(int argc, char *argv[])
{
	pthread_t	*philos;
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
	philos = malloc(sizeof(pthread_t) * nphilos);
	init_threads(nphilos, philos);
}
