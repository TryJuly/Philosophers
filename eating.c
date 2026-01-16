/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:14:06 by strieste          #+#    #+#             */
/*   Updated: 2026/01/16 09:41:09 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	drop_fork(t_philo *p, int id);
static int	taking_fork(t_philo *p, int id);
static void	print_fork(int id, long start_time);

int	eat(t_philo *p, int id, long start_time, int eat_time)
{
	taking_fork(p, id);
	pthread_mutex_lock(&p->meal_mutex);
	p->nb_meal++;
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->meal_mutex);
	pthread_mutex_lock(&p->data->write);
	if (p->data->one_dead == 0)
	{
		print_fork(id, start_time);
		pthread_mutex_unlock(&p->data->write);
		ft_smart_sleep(eat_time, p->data);
		drop_fork(p, id);
	}
	else
		return (pthread_mutex_unlock(&p->data->write), drop_fork(p, id), 1);
	return (0);
}

static void	print_fork(int id, long start_time)
{
	if (id % 2 == 0)
	{
		printf("[%ld] %d: Has taken left fork\n", get_time() - start_time, id);
		printf("[%ld] %d: Has taken right fork\n", get_time() - start_time, id);
	}
	else
	{
		printf("[%ld] %d: Has taken right fork\n", get_time() - start_time, id);
		printf("[%ld] %d: Has taken left fork\n", get_time() - start_time, id);
	}
	printf("[%ld] %d: Is eating\n", get_time() - start_time, id);
	return ;
}

static int	taking_fork(t_philo *p, int id)
{
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&p->data->forks[p->l_fork]);
		pthread_mutex_lock(&p->data->forks[p->r_fork]);
	}
	else
	{
		pthread_mutex_lock(&p->data->forks[p->r_fork]);
		pthread_mutex_lock(&p->data->forks[p->l_fork]);
	}
	return (0);
}

static int	drop_fork(t_philo *p, int id)
{
	if (id % 2 == 0)
	{
		pthread_mutex_unlock(&p->data->forks[p->l_fork]);
		pthread_mutex_unlock(&p->data->forks[p->r_fork]);
	}
	else
	{
		pthread_mutex_unlock(&p->data->forks[p->r_fork]);
		pthread_mutex_unlock(&p->data->forks[p->l_fork]);
	}
	return (0);
}
