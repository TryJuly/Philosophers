/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:16:43 by strieste          #+#    #+#             */
/*   Updated: 2026/01/19 10:59:05 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	loop_routine(t_philo *p);
static void	loop_routine_odd(t_philo *p);
static int	thinking(t_philo *p, int id, long start_time);
static int	sleeping(t_philo *p, int id, long start_time);

void	*routine(void *data)
{
	t_philo	*p;

	p = data;
	if (before_start(p) == 1)
		return (NULL);
	if (p->data->nb_philo == 1)
		return (ft_smart_sleep(p->data->time_die, p->data), NULL);
	if (p->id % 2 == 0)
	{
		ft_smart_sleep(p->data->time_eat / 2, p->data);
		loop_routine_odd(p);
	}
	else
		loop_routine(p);
	return (NULL);
}

static void	loop_routine(t_philo *p)
{
	int		id;
	int		must_eat;
	int		eat_time;
	long	start_time;

	id = p->id + 1;
	start_time = p->data->time;
	must_eat = p->data->must_eat;
	eat_time = p->data->time_eat;
	while (1)
	{
		if ((must_eat != -1) && check_must_eat(p) == 1)
			break ;
		if (eat(p, id, start_time, eat_time))
			break ;
		if (sleeping(p, id, start_time))
			break ;
		if (thinking(p, id, start_time))
			break ;
	}
	return ;
}

static void	loop_routine_odd(t_philo *p)
{
	int		id;
	int		must_eat;
	int		eat_time;
	long	start_time;

	id = p->id + 1;
	start_time = p->data->time;
	must_eat = p->data->must_eat;
	eat_time = p->data->time_eat;
	while (1)
	{
		if ((must_eat != -1) && check_must_eat(p) == 1)
			break ;
		if (thinking(p, id, start_time))
			break ;
		if (eat(p, id, start_time, eat_time))
			break ;
		if (sleeping(p, id, start_time))
			break ;
	}
	return ;
}

static int	sleeping(t_philo *p, int id, long start_time)
{
	pthread_mutex_lock(&p->data->write);
	if (p->data->one_dead == 0)
	{
		printf("[%ld] %d: Is sleeping\n", get_time() - start_time, id);
		pthread_mutex_unlock(&p->data->write);
		ft_smart_sleep(p->data->time_sleep, p->data);
	}
	else
		return (pthread_mutex_unlock(&p->data->write), 1);
	return (0);
}

static int	thinking(t_philo *p, int id, long start_time)
{
	pthread_mutex_lock(&p->data->write);
	if (p->data->one_dead == 0)
	{
		printf("[%ld] %d: Is thinking\n", get_time() - start_time, id);
		pthread_mutex_unlock(&p->data->write);
		ft_smart_sleep(5, p->data);
	}
	else
		return (pthread_mutex_unlock(&p->data->write), 1);
	return (0);
}
