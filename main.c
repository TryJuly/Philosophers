/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:53:56 by strieste          #+#    #+#             */
/*   Updated: 2026/01/06 15:13:45 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *);

int	main(int ac, char **av)
{
	t_data	data;
	(void)ac;
	(void)av;
	
	if (init_data(ac, av, &data))
		return (1);
	
	return (0);
}

// void	*routine(void *data)
// {
// 	t_data	*philo;

// 	philo = (t_data *)data;
// 	// pthread_mutex_lock(&philo->write);
// 	printf("%sHello from id: %d\n%s", BYRED, philo->id, NC);
// 	// pthread_mutex_unlock(&philo->write);
// 	return (NULL);
// }

// int	creat_philosophe(t_data *data)
// {
// 	int	count;
	
// 	data->philosophe = malloc(data->number_philo * sizeof(data->philosophe));
// 	if (!data->philosophe)
// 		return (1);
// 	count = 0;
// 	while (count < data->number_philo)
// 	{
// 		pthread_mutex_lock(&data->lock_philo);
// 		if (pthread_create(&data->philosophe[data->id], NULL, routine, &(*data)) != 0)
// 			return (printf("Error creat thread\n"), 1);
// 		usleep(5);
// 		data->id++;
// 		pthread_mutex_unlock(&data->lock_philo);
// 		count++;
// 	}
// 	return (0);
// }
