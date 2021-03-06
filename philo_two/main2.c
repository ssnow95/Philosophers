/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:58:09 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/13 21:05:20 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int					first_fork(int start, t_all *all)
{
	sem_wait(all->table->forks);
	if ((start = get_time(all)) - all->philo->start > all->info->death)
	{
		sem_post(all->table->forks);
		all->death = 1;
		return (1);
	}
	else
	{
		sem_wait(all->table->sem_print);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(all->philo->name, 1);
		write(1, " has taken a right fork\n", 24);
		sem_post(all->table->sem_print);
	}
	return (0);
}

int					second_fork(int start, t_all *all)
{
	sem_wait(all->table->forks);
	if ((start = get_time(all)) - all->philo->start > all->info->death)
	{
		sem_post(all->table->forks);
		sem_post(all->table->forks);
		all->death = 1;
		return (1);
	}
	else
	{
		sem_wait(all->table->sem_print);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(all->philo->name, 1);
		write(1, " has taken a left fork\n", 23);
		sem_post(all->table->sem_print);
	}
	return (0);
}

int					eating(int start, t_all *all)
{
	if ((start = get_time(all)) - all->philo->start > all->info->death)
	{
		sem_post(all->table->forks);
		sem_post(all->table->forks);
		all->death = 1;
		return (1);
	}
	else
	{
		sem_wait(all->table->sem_print);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(all->philo->name, 1);
		write(1, " is eating\n", 11);
		sem_post(all->table->sem_print);
	}
	return (0);
}

int					eat(t_all *all)
{
	long long int	finish;
	long long int	start;

	start = 0;
	if (first_fork(start, all) == 1)
		return (1);
	if (second_fork(start, all) == 1)
		return (1);
	if (eating(start, all) == 1)
		return (1);
	start = get_time(all);
	finish = start;
	all->philo->start = finish;
	while ((finish = get_time(all)) - start < all->info->eat)
		usleep(1);
	sem_post(all->table->forks);
	sem_post(all->table->forks);
	usleep(50);
	return (0);
}

int					sleep_philo(t_all *all)
{
	long int		start;
	long int		finish;

	if ((start = get_time(all)) - all->philo->start > all->info->death)
	{
		all->death = 1;
		return (1);
	}
	else
	{
		sem_wait(all->table->sem_print);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		ft_putnbr_fd(all->philo->name, 1);
		write(1, " is sleeping\n", 13);
		sem_post(all->table->sem_print);
	}
	start = get_time(all);
	finish = start;
	while ((finish = get_time(all)) - start < all->info->sleep)
		usleep(1);
	return (0);
}
