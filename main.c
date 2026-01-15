/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:53:56 by strieste          #+#    #+#             */
/*   Updated: 2026/01/15 20:10:42 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_input(int ac, char **av);
static int	start_simulation(t_data *data);
static int	clean_all(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac < 5 || ac > 6)
		return (error_input(), 1);
	if (check_input(ac, av) == 1)
		return (1);
	memset(&data, 0, sizeof(data));
	if (init_data(ac, av, &data))
		return (1);
	start_simulation(&data);
	clean_all(&data);
	return (0);
}

static int	start_simulation(t_data *data)
{
	if (creat_monitor(data) == 1)
		return (-1);
	if (launch_philo(data) == 1)
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

static int	check_input(int ac, char **av)
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
		if (av[len][count] < '0' || av[len][count] > '9')
			return (p_error("Program take only digit\n"), 1);
		while (av[len][count])
		{
			if (ft_isdigit(av[len][count]) == 0)
				return (p_error("Function take only digit\n"), 1);
			count++;
		}
		len++;
	}
	return (0);
}
