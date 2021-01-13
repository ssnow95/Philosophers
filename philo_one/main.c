/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:58:09 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/13 20:05:47 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int					parsing(char **argv, t_info *info, int argc)
{
	if (argv != NULL)
	{
		info->sum_phil = ft_atoi(argv[1]);
		info->death = ft_atoi(argv[2]);
		info->eat = ft_atoi(argv[3]);
		info->sleep = ft_atoi(argv[4]);
		if (argc == 6)
			info->must_eat = ft_atoi(argv[5]);
		else
			info->must_eat = -1;
		if (info->sum_phil > 200 || info->sum_phil < 2)
		{
			write(2, "incorrect sum philosophers\n", 27);
			return (1);
		}
		if (argc == 6 && info->must_eat <= 0)
		{
			write(2, "incorrect sum args[5]\n", 22);
			return (1);
		}
		return (0);
	}
	else
		return (1);
	return (0);
}

int					think(t_all *all)
{
	long long int	start;

	if ((start = get_time(all)) - all->philo->start > all->info->death)
	{
		all->death = 1;
		return (1);
	}
	else
	{
		pthread_mutex_lock(&all->table->forks[all->info->sum_phil]);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(all->philo->name, 1);
		write(1, " is thinking\n", 13);
		pthread_mutex_unlock(&all->table->forks[all->info->sum_phil]);
	}
	return (0);
}

void				*live(void *args)
{
	t_all *all;

	all = (t_all *)args;
	while (all->death == 0)
	{
		if (all->full_feed == 0)
		{
			if (eat(all) == 0 && sleep_philo(all) == 0 && think(all) == 0)
			{
				if (all->philo->must_eat > 0)
					all->philo->must_eat--;
				if (all->philo->must_eat == 0)
					all->full_feed = 1;
			}
			else
				return (NULL);
		}
	}
	return (NULL);
}

void				main2(int i, t_info *info)
{
	t_all			*all;
	t_table			*table;
	t_philo			*philo;
	pthread_t		thread;

	philo = init_philo(info->sum_phil, info->must_eat);
	table = init_table(info->sum_phil);
	all = init_all(table, philo, info);
	while (i < all->info->sum_phil)
	{
		pthread_create(&(all[i].philo->pthread), NULL, live, (void *)(&all[i]));
		i++;
		usleep(50);
	}
	pthread_create(&thread, NULL, phil_die, (void *)(&all[0]));
	pthread_join(thread, NULL);
	while (i < all->info->sum_phil)
	{
		pthread_detach(all[i].philo->pthread);
		i++;
	}
	pthread_detach(thread);
}

int					main(int argc, char **argv)
{
	t_info			info;
	int				i;

	i = 0;
	if ((argc == 6 || argc == 5) && parsing(argv, &info, argc) == 0)
		main2(i, &info);
	if (argc > 6 || argc < 5)
	{
		write(2, "incorrect sum argc\n", 19);
		return (1);
	}
	return (0);
}
