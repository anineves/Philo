/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:28:29 by asousa-n          #+#    #+#             */
/*   Updated: 2023/05/06 16:07:15 by asousa-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	while (i < data->nbrs_philo)
	{
		if (pthread_create(&data->philo[i]->thread, NULL,
				&ft_routine, data->philo[i]) != 0)
			handle_error("create thread", data);
		i++;
	}
	if (data->nbrs_philo > 1)
	{
		if (pthread_create(&data->ft_control, NULL,
				&ft_control, data) != 0)
			handle_error("create thread", data);
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc < 5 || argc > 6)
	{
		handle_error("invalid number of arguments\n", data);
		return (EXIT_FAILURE);
	}
	if (!ft_verific(argv))
	{
		handle_error("invalid number of arguments\n", data);
		return (EXIT_FAILURE);
	}
	data = ft_init_data(argv);
	if (!data)
		return (EXIT_FAILURE);
	ft_start_simulation(data);
	stop_simulation(data);
	return (EXIT_SUCCESS);
}
