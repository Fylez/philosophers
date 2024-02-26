/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:00:34 by lzaengel          #+#    #+#             */
/*   Updated: 2024/02/26 18:20:20 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


long	ft_atoi( const char *theString)
{
	long			i;
	long			result;
	int				neg;

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


int	check_args(int argc, char **arg)
{
	int	i;

	i = 1;
	while (i <= argc)
	{
		if (i != 5)
		{
			if (ft_atoi(arg[i]) <= 0)
				return (0);
		}
		if (i == 5)
		{
			if (ft_atoi(arg[i]) < 0)
				return (0);
		}
		i++;
	}
}
