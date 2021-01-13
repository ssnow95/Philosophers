/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:58:09 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/13 20:56:33 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int						parsing(char **argv, t_info *info, int argc)
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
		else if (argc == 6 && info->must_eat <= 0)
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

void					*live(void *args)
{
	t_all				*all;

	all = (t_all *)args;
	pthread_create(&all->philo->philo, NULL, phil_die, (void *)all);
	while (1)
	{
		if (all->full_feed == 0)
		{
			eat(all);
			sleep_philo(all);
			think(all);
		}
		if (all->philo->must_eat > 0)
			all->philo->must_eat--;
		if (all->philo->must_eat == 0)
			all->full_feed = 1;
	}
	return (NULL);
}

void					make_fork(int i, int j, t_all *all, int stat)
{
	int					g_status;

	while (i < all->info->sum_phil)
	{
		all[i].philo->pid = fork();
		if (all[i].philo->pid == 0)
			live(&all[i]);
		else if (all[i].philo->pid < 0)
		{
			write(2, "error: fatal\n", 13);
			exit(free_struct(all));
		}
		i++;
		usleep(50);
	}
	i = 0;
	while (waitpid(-1, &stat, 0) && ++j != all->info->sum_phil)
	{
		g_status = WEXITSTATUS(stat);
		if (g_status == 1 || g_status == -1)
			while (i < all->info->sum_phil)
				kill(all[i++].philo->pid, SIGKILL);
	}
	free_struct(all);
	exit(0);
}

int						main(int argc, char **argv)
{
	t_all			*all;
	t_table			*table;
	t_philo			*philo;
	t_info			info;

	if ((argc == 6 || argc == 5) && parsing(argv, &info, argc) == 0)
	{ 
		philo = init_philo(info.sum_phil, info.must_eat);
		table = init_table(info.sum_phil);
		all = init_all(table, philo, &info);
		make_fork(0, 0, all, 0);
	}
	if (argc > 6 || argc < 5)
	{
		write(2, "incorrect sum argc\n", 19);
		return (1);
	}
	return (0);
}
