/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 06:45:39 by aasselma          #+#    #+#             */
/*   Updated: 2023/06/09 01:13:54 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "philo_bonus.h"

long	ft_atoi(char *s)
{
	long	r;
	long	sign;
	long	i;

	r = 0;
	sign = 1;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		r = r * 10 + s[i++] - '0';
	if ((r * sign) <= 0)
	{
		write(2, "Error\n", 6);
		exit(0);
	}
	return (r * sign);
}

long	t_now(void)
{
	struct timeval	tv;
	long			befor;

	gettimeofday(&tv, NULL);
	befor = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
	return (befor);
}

int	ft_printf(char *str, t_philo *philo)
{
	long	tm;

	tm = philo->data->tm;
	sem_wait(philo->data->lock_death);
	if (philo->data->dead == 0)
	{
		printf("%ld %d %s", t_now() - tm, philo->id + 1, str);
		sem_post(philo->data->lock_death);
	}
	else
	{
		sem_post(philo->data->lock_death);
		return (1);
	}
	return (0);
}

void	fill_data(t_data *data, int ph_num, long die_t, long eat_t)
{
	sem_t	*death_lock;
	sem_t	*last_eat_lock;
	sem_t	times_of_eat;

	sem_unlink("/death_lock");
	sem_unlink("/last_eat_lock");
	sem_unlink("/counter");
	data->tm = t_now();
	last_eat_lock = sem_open("/last_eat_lock", O_CREAT, 0644, 1);
	death_lock = sem_open("/death_lock", O_CREAT, 0644, 1);
	data->counter = &times_of_eat;
	data->counter = sem_open("/counter", O_CREAT, 0644, 1);
	data->ph_num = ph_num;
	data->die_time = die_t;
	data->eat_time = eat_t;
	data->dead = 0;
	data->lock_last = last_eat_lock;
	data->lock_death = death_lock;
}

void	fill_data_of_threads(t_philo *th, t_data *dt, int n_o_e)
{
	int		i;

	sem_unlink("/forks");
	i = 0;
	while (i != dt->ph_num)
	{
		th[i].num_ot_eat = n_o_e;
		th[i].last_eat = t_now();
		th[i].id = i;
		th[i].forks = sem_open("/forks", O_CREAT, 0644, dt->ph_num);
		i++;
	}
}
