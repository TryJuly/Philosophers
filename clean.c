/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:32:00 by strieste          #+#    #+#             */
/*   Updated: 2026/01/12 12:35:26 by strieste         ###   ########.fr       */
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

void	destroy_mutex_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_destroy(&data->philos[i++].meal_mutex);
}

void	destroy_mutex_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->die);
}