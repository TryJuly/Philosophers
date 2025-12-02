/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:53:56 by strieste          #+#    #+#             */
/*   Updated: 2025/12/02 11:51:34 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creat_philosophe(t_data *data);
void	*routine(void *);

int	main(int ac, char **av)
{
	t_data		philo;
	int			count;

	count = 1;
	set_clean(&philo);
	check_argument(ac - 1, av, &philo);
	printf("%s#######################################%s\n", LGREEN, NC);
	printf("%sNumbers philo: %d%s\n", BLUE, philo.number_philo, NC);
	printf("%s#######################################%s\n", LGREEN, NC);
	pthread_mutex_init(&philo.write, NULL);
	pthread_mutex_init(&philo.lock_philo, NULL);
	creat_philosophe(&philo);
	while (count < philo.number_philo)
	{
		pthread_join(philo.philosophe[count], NULL);
		count++;
	}
	pthread_mutex_destroy(&philo.write);
	pthread_mutex_destroy(&philo.lock_philo);
	(void)ac;
	(void)av;
	return (0);
}

void	*routine(void *data)
{
	t_data	*philo;

	philo = (t_data *)data;
	// pthread_mutex_lock(&philo->write);
	printf("%sHello from id: %d\n%s", BYRED, philo->id, NC);
	// pthread_mutex_unlock(&philo->write);
	return (NULL);
}

int	creat_philosophe(t_data *data)
{
	int	count;
	
	data->philosophe = malloc(data->number_philo * sizeof(data->philosophe));
	if (!data->philosophe)
		return (1);
	count = 0;
	while (count < data->number_philo)
	{
		pthread_mutex_lock(&data->lock_philo);
		if (pthread_create(&data->philosophe[data->id], NULL, routine, &(*data)) != 0)
			return (printf("Error creat thread\n"), 1);
		usleep(5);
		data->id++;
		pthread_mutex_unlock(&data->lock_philo);
		count++;
	}
	return (0);
}
