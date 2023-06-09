/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routin_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:15:00 by aasselma          #+#    #+#             */
/*   Updated: 2023/06/09 15:17:51 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
	
int	sign = 1;

void	my_usleep(long sleep_time)
{
	long	now;

	now = t_now();
	while (1)
	{
		if ((t_now() - now) >= sleep_time)
			break ;
		usleep(50);
	}
}

void	kill___philo(t_philo *philo)
{
	long	tm;

	tm = philo->data->tm;
	usleep(philo->data->die_time * 1000);
}

int	ft_sleep(t_philo *philo)
{
	int	checker;

	checker = ft_printf("is sleeping\n", philo);
	usleep(philo->data->sleep_time * 1000);
	return (checker);
}

int	ft_routin(t_philo *philo)
{
	int	right_id;
	int	checker;

	right_id = philo->id + 1;
	if (philo->id + 1 == philo->data->ph_num)
		right_id = 0;
	sem_wait(philo->forks);
	checker = ft_printf("has taken a fork\n", philo);
	if (philo->data->ph_num == 1)
		kill___philo(philo);
	sem_wait(philo->forks);
	checker = ft_printf("has taken a fork\n", philo);
	checker = ft_printf("is eating\n", philo);
	sem_wait(philo->data->lock_last);
	philo->last_eat = t_now();
	sem_post(philo->data->lock_last);
	usleep(philo->data->eat_time * 1000);
	sem_wait(philo->data->counter);
	if (philo->data->argc == 6)
		philo->num_ot_eat--;
	sem_post(philo->data->counter);
	sem_post(philo->forks);
	sem_post(philo->forks);
	return (checker);
}

void	*check_death(void *th)
{
	t_philo	*thread;
	int	i;
	
	thread = (t_philo *)th;
	i = 0;
	while (1)
	{
		sem_wait(thread->data->lock_last);
		if ((t_now() - thread->last_eat) >= thread->data->die_time)
		{
			ft_printf("died\n", thread);
			exit(0);
			sem_post(thread->data->lock_death);
		}
		sem_post(thread->data->lock_last);
		if (i >= thread->data->ph_num - 1)
			i = 0;
		i++;
		usleep(100);
	}
	return (NULL);
}
