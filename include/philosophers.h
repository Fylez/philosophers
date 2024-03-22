/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:20:19 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/22 16:48:32 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table {
	pthread_mutex_t	*fork;
	pthread_mutex_t	text;
	pthread_mutex_t	stop;
	struct timeval	start_time;
	int				nphilos;
	int				tdie;
	int				teat;
	int				tsleep;
	int				aeat;
	int				tostop;
	int				pdone;
}	t_table;

typedef struct s_philo {
	int				index;
	t_table			*table;
	pthread_t		philo;
	int				teaten;
	struct timeval	last_time;
}	t_philo;

int		ft_atoi( const char *theString);
void	ft_exit(char *reason);
void	check_args(int argc, char **arg);
void	*routine(void *philo);
long	get_time_elapsed(struct timeval p_time);
void	ft_print(char *reason, t_philo *philo);
int		checkstop(t_table *table);
void	ft_sleep( t_table *table, int time);
void	ft_print_death(t_philo *philo);

#endif