/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:20:50 by strieste          #+#    #+#             */
/*   Updated: 2026/01/13 11:08:19 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_data *data);
static int	init_philos_struct(t_data *data);
static int	taking_args(int ac, char **av, t_data *data);
static int	init_philo(t_philo *philos, int numbers, t_data *data);

int	init_data(int ac, char **av, t_data *data)
{
	if (check_input(ac, av))
		return (1);
	if (taking_args(ac, av, data))
		return (1);
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (p_error("Error malloc\n"), 1);
	data->philos = malloc(data->nb_philo * sizeof(t_philo));
	if (!data->philos)
		return (free(data->forks), printf("Error malloc\n"), 1);
	if (init_mutex(data))
		return (p_error("Error init mutex\n"), free_data(data), 1);
	if (init_philos_struct(data))
		return (destroy_mutex_data(data), free_data(data), 1);
	data->stop = 0;
	data->error = 0;
	data->one_dead = 0;
	return (0);
}

static int	init_mutex(t_data *data)
{
	int index;
	
	index = 0;
	while (index < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[index], NULL) != 0)
			return (destroy_mutex_loop(data, index), 1);
		index++;
	}
	if (pthread_mutex_init(&data->error_check, NULL) != 0)
		return (destroy_mutex_loop(data, data->nb_philo), 1);
	if (pthread_mutex_init(&data->write, NULL) != 0)
	{
		destroy_mutex_loop(data, data->nb_philo);
		pthread_mutex_destroy(&data->error_check);
		return (1);
	}
	if (pthread_mutex_init(&data->die, NULL) != 0)
	{
		destroy_mutex_loop(data, data->nb_philo);
		pthread_mutex_destroy(&data->error_check);
		pthread_mutex_destroy(&data->write);
		return (1);
	}
	return (0);
}

static int	init_philos_struct(t_data *data)
{
	int	index;
	int	count;

	index = 0;
	while (index < data->nb_philo)
	{
		if (init_philo(&data->philos[index], index, data))
		{
			count = 0;
			while (count < index)
				pthread_mutex_destroy(&data->philos[count++].meal_mutex);
			return (p_error("Error Init mutex\n"), 1);
		}
		index++;
	}
	return (0);
}

static int	init_philo(t_philo *philos, int numbers, t_data *data)
{
	philos->id = numbers;
	philos->l_fork = numbers;
	philos->r_fork = (numbers + 1) % data->nb_philo;
	philos->last_meal = get_time();
	philos->nb_meal = 0;
	philos->data = data;
	if (pthread_mutex_init(&philos->meal_mutex, NULL) != 0)
		return (p_error("Error init mutex\n"), 1);
	return (0);
}

static int	taking_args(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo < 1 || !data->nb_philo)
		return (p_error("Number of philo less than 1\n"), 1);
	data->time_die = ft_atoi(av[2]);
	if (data->time_die < 0 || !data->time_die)
		return (p_error("Time die without eating less than 1\n"), 1);
	data->time_eat = ft_atoi(av[3]);
	if (data->time_eat < 0 || !data->time_eat)
		return (p_error("Time for eat Invalid input\n"), 1);
	data->time_sleep = ft_atoi(av[4]);
	if (data->time_sleep < 0 || !data->time_sleep)
		return (p_error("Time take to sleep less than 1\n"), 1);
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		if (data->must_eat < 0 || !data->must_eat)
			return (p_error("Number of time need eat less than 1\n"), 1);
	}
	else if (ac == 5)
		data->must_eat = -1;
	return (0);
}

int	check_input(int ac, char **av)
{
	int		len;
	size_t	count;

	len = 1;
	while (len < ac)
	{
		count = 0;
		if (av[len][count] == '+')
			count++;
		if (av[len][count] == '+')
			return (p_error("No two '+'\n"), 1);
		if (av[len][count] == '-')
			return (p_error("No negative numbers\n"), 1);
		while (av[len][count])
		{
			if (!ft_isdigit(av[len][count]))
				return (p_error("Function take only digit\n"), 1);
			count++;
		}
		len++;
	}
	return (0);
}
