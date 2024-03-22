/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:00:34 by lzaengel          #+#    #+#             */
/*   Updated: 2024/03/22 16:48:46 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_exit(char *reason)
{
	printf("%s\n", reason);
	exit (0);
}

int	ft_isdigit(int character)
{
	if (character < '0' || character > '9')
	{
		return (0);
	}
	return (1);
}

int	ft_atoi( const char *theString)
{
	int			i;
	int			result;
	int			neg;

	i = 0;
	neg = 1;
	result = 0;
	if (theString[i] == '-')
		return (-1);
	else if (theString[i] == '+')
		i++;
	while (theString[i])
	{
		if (ft_isdigit(theString[i]))
		{
			result = result * 10 + theString[i] - '0';
			i++;
		}
		else
			return (-1);
	}
	return (result * neg);
}

void	check_args(int argc, char **arg)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (i != 5)
		{
			if (ft_atoi(arg[i]) <= 0)
				ft_exit("Arguments are invalid");
		}
		else if (i == 5)
		{
			if (ft_atoi(arg[i]) < 0)
				ft_exit("Arguments are invalid");
		}
		i++;
	}
}
