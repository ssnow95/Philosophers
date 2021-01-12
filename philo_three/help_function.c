/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:01:33 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/12 20:59:01 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int					ft_atoi(const char *str)
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

static int			sum_num(int n)
{
	int				sum;

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

static char			count_itoa(char *arr, int n, int sum)
{
	int				copy_int;
	char			*b;

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

char				*ft_itoa(int n)
{
	char			*arr;
	int				sum;
	int				i;

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

void				free_struct(t_all *all)
{
	sem_close(all->table->forks);
	sem_close(all->table->sem_print);
	free(all);
}