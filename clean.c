/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:32:00 by strieste          #+#    #+#             */
/*   Updated: 2026/01/06 16:23:52 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	destroy_mutex_loop(t_data *data, int numbers)
{
	int	index;

	index = 0;
	while (index < numbers)
	{
		pthread_mutex_destroy(&data->forks[index]);
		index++;
	}
}