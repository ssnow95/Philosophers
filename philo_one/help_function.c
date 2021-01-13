/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:01:33 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/13 16:59:23 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int						ft_atoi(const char *str)
{
	int					b;
	long long int		res;

	res = 0;
	b = 1;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if ((*str == '-'))
		b = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		if (res > ((res * 10) + (*str - '0')) && b == 1)
			return (-1);
		else if (res > ((res * 10) + (*str - '0')) && b == -1)
			return (0);
		else
			res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * b);
}

void					ft_putstr_fd(char *s, int fd)
{
	int					i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

long long int			get_time(t_all *all)
{
	long long int		finish;
	struct timeval		tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	finish = (unsigned int)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
	return (finish - all->start);
}

void					ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void					ft_putnbr_fd(int n, int fd)
{
	int min;

	min = -2147483648;
	if (n < 0 && n != min)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n == min)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}
