/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:53:56 by strieste          #+#    #+#             */
/*   Updated: 2026/01/14 10:39:54 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_simulation(t_data *data);
static int	clean_all(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;
	
	(void)av;
	if (ac < 5 || ac > 6)
		return (error_input(), 1);
	if (init_data(ac, av, &data))
		return (1);
	start_simulation(&data);
	clean_all(&data);
	return (0);
}

static int	start_simulation(t_data *data)
{
	if (creat_monitor(data))
		return (-1);
	data->time = get_time();
	if (launch_philo(data))
		return (-1);
	join_philo(data);
	pthread_join(data->monitor, NULL);
	return (0);
}

static int	clean_all(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_philo)
		pthread_mutex_destroy(&data->philos[index++].meal_mutex);
	free(data->philos);
	index = 0;
	while (index < data->nb_philo)
		pthread_mutex_destroy(&data->forks[index++]);
	free(data->forks);
	pthread_mutex_destroy(&data->error_check);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->die);
	return (0);
}
