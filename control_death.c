/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:27:45 by asousa-n          #+#    #+#             */
/*   Updated: 2023/05/06 16:17:57 by asousa-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_die_philo(t_philo *philo)
{
	time_t	time;

	time = ft_get_time();
	if ((time - philo->last_meal) > philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->sim_stop_lock);
		philo->data->stop = true;
		pthread_mutex_unlock(&philo->data->sim_stop_lock);
		ft_print(philo, true, "died 🤧");
		pthread_mutex_unlock(&philo->eat_lock);
		return (true);
	}
	return (false);
}

static bool	ft_can_stop(t_data *data)
{
	int		i;
	bool	meals_check;

	meals_check = true;
	i = 0;
	while (i < data->nbrs_philo)
	{
		pthread_mutex_lock(&data->philo[i]->eat_lock);
		if (ft_die_philo(data->philo[i]))
			return (true);
		if (data->must_eat != -1)
			if (data->philo[i]->meals_count < data->must_eat)
				meals_check = false;
		pthread_mutex_unlock(&data->philo[i]->eat_lock);
		i++;
	}
	if (data->must_eat != -1 && meals_check == true)
	{
		pthread_mutex_lock(&data->sim_stop_lock);
		data->stop = true;
		pthread_mutex_unlock(&data->sim_stop_lock);
		return (true);
	}
	return (false);
}

void	*ft_control(void *info)
{
	t_data			*data;

	data = (t_data *)info;
	while (true)
	{
		if (ft_can_stop(data) == true)
			break ;
	}
	return (NULL);
}
