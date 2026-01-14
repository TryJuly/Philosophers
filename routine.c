/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:16:43 by strieste          #+#    #+#             */
/*   Updated: 2026/01/13 17:42:12 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thinking(t_philo *p);
static int	sleeping(t_philo *p);
static int	check_must_eat(t_philo *p);

void	*routine(void *data)
{
	t_philo	*p;

	p = data;
	pthread_mutex_lock(&p->data->error_check);
	if (p->data->error != 0)
		return (pthread_mutex_unlock(&p->data->error_check), NULL);
	pthread_mutex_unlock(&p->data->error_check);
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->meal_mutex);
	while (1)
	{
		if (p->data->must_eat != -1 && check_must_eat(p) == 1)
				break ;
		if (eat(p))
			break ;
		if (sleeping(p))
			break ;
		if (thinking(p))
			break ;
	}
	return (NULL);
}

static int	check_must_eat(t_philo *p)
{
	pthread_mutex_lock(&p->data->error_check);
	if (p->data->stop == 1)
		return (pthread_mutex_unlock(&p->data->error_check), 1);
	pthread_mutex_unlock(&p->data->error_check);
	return (0);
}

static int	thinking(t_philo *p)
{
	pthread_mutex_lock(&p->data->write);
	if (check_dead(p->data) == 0)
	{
		printf("[%ld] %d is thinking\n", get_time() - p->data->time, p->id + 1);
		pthread_mutex_unlock(&p->data->write);
		smart_sleep(50, p->data);
	}
	else
	{
		pthread_mutex_unlock(&p->data->write);
		return (1);
	}
	return (0);
}

static int	sleeping(t_philo *p)
{
	pthread_mutex_lock(&p->data->write);
	if (check_dead(p->data) == 0)
	{
		printf("[%ld] %d is sleeping\n", get_time() - p->data->time, p->id + 1);
		pthread_mutex_unlock(&p->data->write);
		smart_sleep(p->data->time_sleep, p->data);
	}
	else
	{
		pthread_mutex_unlock(&p->data->write);
		return (1);
	}
	return (0);
}

int	check_dead(t_data *p)
{
	int states;
	
	pthread_mutex_lock(&p->die);
	states = p->one_dead;
	pthread_mutex_unlock(&p->die);
		if (states != 0)
			return (1);
	return (0);
}
