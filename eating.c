/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:14:06 by strieste          #+#    #+#             */
/*   Updated: 2026/01/14 10:58:10 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating(t_philo *p);
static int	drop_fork(t_philo *p);
static int	taking_fork(t_philo *p);
static int	help_taking_fork(t_philo *p);

int	eat(t_philo *p)
{
	if (check_dead(p->data) != 0)
		return (1);
	if (taking_fork(p))
		return (1);
	if (eating(p))
		return (1);
	if (drop_fork(p))
		return (1);
	return (0);
}

static int	taking_fork(t_philo *p)
{
	if (p->id % 2 == 0 && check_dead(p->data) == 0)
	{
		pthread_mutex_lock(&p->data->forks[p->l_fork]);
		// printf("[%ld]Take l fork id : %d\n",get_time() - p->data->time, p->id);
		pthread_mutex_lock(&p->data->forks[p->r_fork]);
		// printf("[%ld]Take r fork id : %d\n",get_time() - p->data->time, p->id);
		// pthread_mutex_lock(&p->data->write);
		// if (check_dead(p->data) == 0)
		// {
		// 	printf("[%ld] %d has taken a fork\n", get_time() - p->data->time, p->id + 1);
		// 	pthread_mutex_unlock(&p->data->write);
		// }
		// else
			// return (pthread_mutex_unlock(&p->data->write), drop_fork(p), 1);
	}
	else
		if (help_taking_fork(p))
			return (1);
	return (0);
}

static int	help_taking_fork(t_philo *p)
{
	pthread_mutex_lock(&p->data->forks[p->r_fork]);
	// printf("[%ld]Take r fork id : %d\n", get_time() - p->data->time, p->id);
	pthread_mutex_lock(&p->data->forks[p->l_fork]);
	// printf("[%ld]Take l fork id : %d\n", get_time() - p->data->time, p->id);
	// pthread_mutex_lock(&p->data->write);
	// if (check_dead(p->data) == 0)
	// {
	// 	printf("[%ld] %d has taken a fork\n", get_time() - p->data->time, p->id + 1);
	// 	pthread_mutex_unlock(&p->data->write);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(&p->data->write);
	// 	drop_fork(p);
	// 	return (1);
	// }
	return (0);
}

static int	eating(t_philo *p)
{
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal = get_time();
	p->nb_meal++;
	pthread_mutex_lock(&p->data->write);
	if (check_dead(p->data) == 0)
	{
		printf("[%ld] %d has taken a fork\n", get_time() - p->data->time, p->id + 1);
		printf("[%ld] %d is eating\n", get_time() - p->data->time, p->id + 1);
		pthread_mutex_unlock(&p->meal_mutex);
		pthread_mutex_unlock(&p->data->write);
		smart_sleep(p->data->time_eat, p->data);
	}
	else
	{
		pthread_mutex_unlock(&p->data->write);
		drop_fork(p);
		return (1);
	}
	return (0);
}

static int	drop_fork(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_unlock(&p->data->forks[p->l_fork]);
		// printf("[%ld]Drope l fork id : %d\n", get_time() - p->data->time, p->id);
		pthread_mutex_unlock(&p->data->forks[p->r_fork]);
		// printf("[%ld]Drope r fork id : %d\n", get_time() - p->data->time, p->id);
	}
	else
	{
		pthread_mutex_unlock(&p->data->forks[p->r_fork]);
		// printf("[%ld]Drope r fork id : %d\n", get_time() - p->data->time, p->id);
		pthread_mutex_unlock(&p->data->forks[p->l_fork]);
		// printf("[%ld]Drope l fork id : %d\n", get_time() - p->data->time, p->id);
	}
	return (0);
}
