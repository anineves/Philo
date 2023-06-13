/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verific.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:29:06 by asousa-n          #+#    #+#             */
/*   Updated: 2023/05/06 13:10:56 by asousa-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + (str[i] - '0'));
		i++;
	}
	return (res);
}

long int	ft_atol(const char *str)
{
	long	res;
	int		signal;
	int		i;

	res = 0;
	signal = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + (str[i] - '0'));
		i++;
	}
	return (res * signal);
}

static int	ft_check_int(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atol(argv[i]) > 2147483647 || ft_atol(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_verific(char **argv)
{
	if (ft_check_digit(argv) && ft_check_int(argv))
		return (1);
	return (0);
}
