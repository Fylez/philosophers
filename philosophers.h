/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:20:19 by lzaengel          #+#    #+#             */
/*   Updated: 2024/02/28 18:11:57 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_table {
	pthread_mutex_t lock;
}	t_table;

typedef struct s_philo {
	int index;
	t_table *table;
	pthread_t philo;
}	t_philo;

long	ft_atoi( const char *theString);
void	ft_exit(char *reason);
int		check_args(int argc, char **arg);

#endif