/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:13:18 by strieste          #+#    #+#             */
/*   Updated: 2026/01/13 11:28:48 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_philo(t_data *data)
{
	int i;
	int	j;
	
	i = 0;
	j = 1;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
			&data->philos[i]) != 0)
		{
			data->error = 1;
			printf("Error create philo number: %d\n", (i + 1));
			return (1);
		}
		i += 2;
	}
	while (j < data->nb_philo)
	{
		if (pthread_create(&data->philos[j].thread, NULL, &routine,
			&data->philos[j]) != 0)
		{
			data->error = 1;
			printf("Error create philo number: %d\n", (j + 1));
			return (1);
		}
		j += 2;
	}
	return (0);
}

int	join_philo(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			if (pthread_mutex_lock(&data->error_check) != 0)
			{
				p_error("Error lock mutex\n");
				data->error = 1;
				break ;
			}
			data->error = 1;
			pthread_mutex_unlock(&data->error_check);
			printf("Error joint philo number: %d\n", (i + 1));
			return (1);
		}
		i++;
	}
	return (1);
}
