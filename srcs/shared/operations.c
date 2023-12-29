/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:41:37 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/22 15:41:37 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	swap(t_data *data, char flag)
{
	long	temp;

	if (data->a.size >= 2 && (flag == 'a' || flag == 'r'))
	{
		temp = data->a.arr[data->a.start];
		data->a.arr[data->a.start]
			= data->a.arr[(data->a.start + 1) % data->a.size];
		data->a.arr[(data->a.start + 1) % data->a.size] = temp;
	}
	if (data->b.size >= 2 && (flag == 'b' || flag == 'r'))
	{
		temp = data->b.arr[data->b.start];
		data->b.arr[data->b.start]
			= data->b.arr[(data->b.start + 1) % data->b.size];
		data->b.arr[(data->b.start + 1) % data->b.size] = temp;
	}
	write(1, "s", 1);
	write(1, &flag, 1);
	write(1, "\n", 1);
}

void	push(t_data *data, char flag)
{
	if (data->b.size >= 1 && flag == 'a')
	{
		ft_memmove(data->a.arr + data->a.start + 1, data->a.arr
			+ data->a.start, 8 * (data->a.size - data->a.start));
		data->a.arr[data->a.start] = data->b.arr[data->b.start];
		ft_memmove(data->b.arr + data->b.start, data->b.arr
			+ data->b.start + 1, 8 * (data->b.size - data->b.start - 1));
		data->b.arr[data->b.size-- - 1] = (long)INT32_MAX + 1;
		data->a.size++;
		data->b.start = data->b.start % (data->b.size + (data->b.size == 0));
	}
	if (data->a.size >= 1 && flag == 'b')
	{
		ft_memmove(data->b.arr + data->b.start + 1, data->b.arr
			+ data->b.start, 8 * (data->b.size - data->b.start));
		data->b.arr[data->b.start] = data->a.arr[data->a.start];
		ft_memmove(data->a.arr + data->a.start, data->a.arr
			+ data->a.start + 1, 8 * (data->a.size - data->a.start - 1));
		data->a.arr[data->a.size-- - 1] = (long)INT32_MAX + 1;
		data->b.size++;
		data->a.start = data->a.start % (data->a.size + (data->a.size == 0));
	}
	write(1, "p", 1);
	write(1, &flag, 1);
	write(1, "\n", 1);
}

void	rotate(t_data *data, char *flag)
{
	if (!flag[1])
	{
		if (data->a.size >= 2 && (flag[0] == 'a' || flag[0] == 'r'))
			data->a.start = (data->a.start + 1 + data->a.size) % data->a.size;
		if (data->b.size >= 2 && (flag[0] == 'b' || flag[0] == 'r'))
			data->b.start = (data->b.start + 1 + data->b.size) % data->b.size;
	}
	else
	{
		if (data->a.size >= 2 && (flag[1] == 'a' || flag[1] == 'r'))
			data->a.start = (data->a.start - 1 + data->a.size) % data->a.size;
		if (data->b.size >= 2 && (flag[1] == 'b' || flag[1] == 'r'))
			data->b.start = (data->b.start - 1 + data->b.size) % data->b.size;
	}
	write(1, "r", 1);
	write(1, flag, 1 + (flag[1] != 0));
	write(1, "\n", 1);
}
