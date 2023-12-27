/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:56:14 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/18 19:56:14 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
//#include "../includes/push_swap.h"

void	init_data(t_data *data, int ac)
{
	int	i;

	data->a.size = ac - 1;
	data->a.start = 0;
	data->b.size = 0;
	data->b.start = 0;
	data->b.arr = NULL;
	data->a.arr = malloc((ac - 1) * sizeof(long));
	if (!data->a.arr)
		error_exit(data, 0);
	data->b.arr = malloc((ac - 1) * sizeof(long));
	if (!data->a.arr)
		error_exit(data, 0);
	i = -1;
	while (++i < ac - 1)
		data->b.arr[i] = (long)INT32_MAX + 1;
}

void	quick_sort(int *arr, int begin, int end)
{
	int	pivot;
	int	i;
	int	j;
	int	temp;

	if (begin < end)
	{
		pivot = arr[end];
		i = begin - 1;
		j = begin - 1;
		while (++i <= end)
		{
			if (arr[i] <= pivot)
			{
				temp = arr[i];
				arr[i] = arr[++j];
				arr[j] = temp;
			}
		}
		quick_sort(arr, begin, j - 1);
		quick_sort(arr, j + 1, end);
	}
}

int	check_doubles(t_data *data)
{
	int		*arr;
	int		i;
	int		res;

	arr = malloc(data->a.size * sizeof(int));
	if (!arr)
		return (0);
	i = -1;
	while (++i < data->a.size)
		arr[i] = data->a.arr[i];
	quick_sort(arr, 0, data->a.size - 1);
	i = -1;
	res = 1;
	while (++i < data->a.size - 1)
		if (arr[i] == arr[i + 1])
			res = 0;
	free(arr);
	return (res);
}

int	check_input(char **av, int ac, t_data *data)
{
	int		i;
	int		j;
	int		sign;
	long	value;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		sign = 1 * (av[i][j] != '-') - 1 * (av[i][j] == '-');
		if (av[i][j] == '-')
			j++;
		value = 0;
		while (av[i][j] >= '0' && av[i][j] <= '9')
		{
			value = value * 10 + (av[i][j++] - 48);
			if (value * sign > 2147483647 || value * sign < -2147483648)
				return (0);
		}
		if (j != ft_strlen(av[i]) || !av[i][0]
			|| (av[i][0] == '-' && !av[i][1]))
			return (0);
		data->a.arr[i - 1] = value * sign;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;
	int		j;

	init_data(&data, ac);
	if (ac == 1)
		error_exit(&data, 1);
	if (!check_input(av, ac, &data) || !check_doubles(&data))
		error_exit(&data, 0);
	merge_sort(&data);
	printf("stack A:\n");
	i = data.a.start - 1;
	j = -1;
	if (data.a.size > 0)
		while (++j < data.a.size)
			printf("%li\n", data.a.arr[++i % data.a.size]);
	printf("stack B:\n");
	i = data.b.start - 1;
	j = -1;
	if (data.b.size > 0)
		while (++j < data.b.size)
			printf("%li\n", data.b.arr[++i % data.b.size]);
	free(data.a.arr);
	free(data.b.arr);
}
