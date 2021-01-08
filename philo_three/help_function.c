/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:01:33 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/03 20:32:05 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		ft_atoi(const char *str)
{
	int				b;
	long long int	res;

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

static int		sum_num(int n)
{
	int		sum;

	sum = 0;
	if (n == -2147483648)
		return (10);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		sum++;
	}
	return (sum);
}

static char		count_itoa(char *arr, int n, int sum)
{
	int		copy_int;
	char	*b;

	b = (char*)arr + sum;
	copy_int = n;
	*b-- = '\0';
	if (n == 0)
		*b = 0 + '0';
	while (copy_int > 0)
	{
		*b-- = (copy_int % 10) + '0';
		copy_int = copy_int / 10;
	}
	return (*arr);
}

char			*ft_itoa(int n)
{
	char	*arr;
	int		sum;
	int		i;

	i = 0;
	sum = sum_num(n);
	if (n < 0)
		sum += 1;
	if (!(arr = (char*)malloc(sizeof(char) * sum + 1)))
		return (NULL);
	if (n < 0)
	{
		arr[i++] = '-';
		n = n * -1;
	}
	if (n == -2147483648)
	{
		arr[i++] = 2 + '0';
		count_itoa(arr, 147483648, sum);
	}
	count_itoa(arr, n, sum);
	return (arr);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

long long int get_time(t_all *all)
{
 long long int finish;
 struct timeval tv;

 if (gettimeofday(&tv, NULL) == -1)
  return (-1);
 finish = (unsigned int)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
//  printf("%lld                %lld\n\n", finish, all[0].start);
 return (finish - all[0].start);
}


void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
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
