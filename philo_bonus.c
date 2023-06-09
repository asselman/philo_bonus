/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:19:15 by aasselma          #+#    #+#             */
/*   Updated: 2023/06/09 15:16:20 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	dead = 0;

int	start_routin(t_philo *philo)
{
	if (ft_routin(philo) == 1)
		return (1);
	if (ft_sleep(philo) == 1)
		return (1);
	return (0);
}

void	*ph_managment(t_philo *philo)
{
	pthread_t	checker;

	pthread_create(&checker, NULL, check_death, philo);
	if ((philo->id + 1) % 2 == 0)
		usleep(100);
	while (1)
	{
		sem_wait(philo->data->counter);
		if ((philo->num_ot_eat != 0 || philo->data->argc == 5))
		{
			sem_post(philo->data->counter);
			ft_printf("is thinking\n", philo);
			start_routin(philo);
			sem_wait(philo->data->lock_last);
			if ((t_now() - philo->last_eat) >= philo->data->die_time)
			{
				exit(0);
				sem_post(philo->data->lock_last);
			}
			sem_post(philo->data->lock_last);
		}
		else
		{
			sem_post(philo->data->counter);
			exit(0);
		}
	}
	return (NULL);
}

void	ft_contune(t_philo *thread, t_data *data, int num_oft_eat)
{
	int	i;
	int	arr[data->ph_num];

	i = 0;
	fill_data_of_threads(thread, data, num_oft_eat);
	while (i < data->ph_num)
	{
		thread[i].data = data;
		thread[i].pid = fork();
		if (thread[i].pid == 0)
			ph_managment(&thread[i]);
		else
			arr[i] = thread[i].pid;
		usleep(10);
		i = i + 2;
	}
	i = 1;
	int status = -1;
	if (data->ph_num != 1)
	{
		while (i < data->ph_num)
		{
			thread[i].data = data;
			thread[i].pid = fork();
			if (thread[i].pid == 0)
				ph_managment(&thread[i]);
			else
				arr[i] = thread[i].pid;
			usleep(10);
			i = i + 2;
		}
	}
	waitpid(-1, &status, 0);
	i = 0;
	while (i != data->ph_num)
		kill(arr[i++], SIGKILL);
}

int	main(int argc, char **argv)
{
	t_philo			*prc;
	t_data			*data;
	int				i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		data = malloc(sizeof(t_data));
		fill_data(data, ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]));
		data->sleep_time = ft_atoi(argv[4]);
		data->argc = argc;
		prc = malloc(data->ph_num * sizeof(t_philo));
		if (argc == 6)
			i = ft_atoi(argv[5]);
		ft_contune(prc, data, i);
	}
	return (0);
}
