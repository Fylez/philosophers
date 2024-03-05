/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:20:19 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/05 17:52:23 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_table {
	pthread_mutex_t *fork;
	pthread_mutex_t text;
}	t_table;

typedef struct s_philo {
	int index;
	t_table *table;
	pthread_t philo;
}	t_philo;

long	ft_atoi( const char *theString);
void	ft_exit(char *reason);
int		check_args(int argc, char **arg);
void	routine(t_table table);

#endif