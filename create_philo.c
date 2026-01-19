/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:13:18 by strieste          #+#    #+#             */
/*   Updated: 2026/01/19 10:58:33 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_philo(t_data *data)
{
	int	i;

	i = 0;
	data->time = get_time();
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
		{
			data->error = 1;
			printf("Error create philo number: %d\n", (i + 1));
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			pthread_mutex_lock(&data->error_check);
			data->error = 1;
			pthread_mutex_unlock(&data->error_check);
			printf("Error joint philo number: %d\n", (i + 1));
			i++;
			continue ;
		}
		i++;
	}
	return (0);
}
