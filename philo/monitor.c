/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:29:35 by strieste          #+#    #+#             */
/*   Updated: 2026/01/19 10:58:49 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*monitor_routine(void *data);
static int	loop_monitor(t_data *p, int *check);

int	creat_monitor(t_data *data)
{
	if (pthread_create(&data->monitor, NULL, &monitor_routine, data) != 0)
		return (p_error("Error create monitor\n"), 1);
	return (0);
}

static void	*monitor_routine(void *data)
{
	int		check;
	t_data	*p;

	p = data;
	ft_smart_sleep(10, p);
	while (p->one_dead == 0)
	{
		check = 0;
		if (loop_monitor(p, &check) == 1)
			return (NULL);
		if ((p->must_eat != -1) && check == p->nb_philo)
		{
			pthread_mutex_lock(&p->error_check);
			p->stop = 1;
			pthread_mutex_unlock(&p->error_check);
			return (NULL);
		}
		ft_smart_sleep(10, p);
	}
	return (NULL);
}

static int	loop_monitor(t_data *p, int *check)
{
	int	index;

	index = 0;
	while (index < p->nb_philo)
	{
		pthread_mutex_lock(&p->philos[index].meal_mutex);
		if ((p->must_eat != -1) && p->philos[index].nb_meal >= p->must_eat)
			*check += 1;
		if ((get_time() - p->philos[index].last_meal) >= p->time_die)
		{
			pthread_mutex_unlock(&p->philos[index].meal_mutex);
			pthread_mutex_lock(&p->write);
			p->one_dead = 1;
			printf("[%ld] %d: is die\n", get_time() - p->time, index + 1);
			pthread_mutex_unlock(&p->write);
			return (1);
		}
		pthread_mutex_unlock(&p->philos[index].meal_mutex);
		index++;
	}
	return (0);
}
