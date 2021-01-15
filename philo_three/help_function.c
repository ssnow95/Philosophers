/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:01:33 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/14 15:57:11 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int					ft_atoi(const char *str)
{
	long long int	res;

	res = 0;
	if ((*str == '-'))
		return (-1);
	while (*str >= 48 && *str <= 57)
	{
		if (res > ((res * 10) + (*str - '0')))
			return (-1);
		else if (res > ((res * 10) + (*str - '0')))
			return (0);
		else
			res = (res * 10) + (*str - '0');
		str++;
	}
	if (res > INT_MAX || *str != '\0')
		res = -1;
	return (res);
}

int					free_struct(t_all *all)
{
	sem_unlink("forks");
	sem_unlink("sem_print");
	sem_close(all->table->forks);
	sem_close(all->table->sem_print);
	free(all);
	return (-1);
}
