/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:21:12 by strieste          #+#    #+#             */
/*   Updated: 2026/01/15 15:55:14 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_dead(t_data *p)
// {
// 	pthread_mutex_lock(&p->die);
// 	if (p->one_dead != 0)
// 		return (pthread_mutex_unlock(&p->die), 1);
// 	pthread_mutex_unlock(&p->die);
// 	return (0);
// }

int	check_must_eat(t_philo *p)
{
	pthread_mutex_lock(&p->data->error_check);
	if (p->data->stop == 1)
		return (pthread_mutex_unlock(&p->data->error_check), 1);
	pthread_mutex_unlock(&p->data->error_check);
	return (0);
}

int	before_start(t_philo *p)
{
	pthread_mutex_lock(&p->data->error_check);
	if (p->data->error != 0)
		return (pthread_mutex_unlock(&p->data->error_check), 1);
	pthread_mutex_unlock(&p->data->error_check);
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->meal_mutex);
	return (0);
}

void	ft_smart_sleep(long time_ms, t_data *p)
{
	long	start;

	start = get_time();
	while (p->one_dead == 0)
	{
		if (get_time() - start >= time_ms)
			break ;
		usleep(1);
	}
	return ;
}
