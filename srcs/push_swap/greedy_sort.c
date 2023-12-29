/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:49:20 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/29 17:00:34 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_position(t_data *data, long nb)
{
	int		j;
	int		counter;
	long	b_max;
	int		index_max;

	j = -1;
	counter = 0;
	b_max = (long)INT32_MIN - 1;
	index_max = -1;
	while (++j < data->b.size)
	{
		if (b_max < data->b.arr[(data->b.start + j) % data->b.size])
		{
			b_max = data->b.arr[(data->b.start + j) % data->b.size];
			index_max = j;
		}
		counter += nb > data->b.arr[(data->b.start + j) % data->b.size];
	}
	if (counter == data->b.size || counter == 0)
		return (index_max);
	while (!(nb
			< data->b.arr[(data->b.start + j - 1 + data->b.size) % data->b.size]
			&& nb > data->b.arr[(data->b.start + j) % data->b.size]))
		j--;
	return (j);
}

void	count_rotates(t_data *data, int i, int *key, int rotates[2])
{
	int	j;
	int	new;

	j = count_position(data, data->a.arr[(data->a.start + i) % data->a.size]);
	new = min(max(i, j), max(data->a.size - i, data->b.size - j),
			i + data->b.size - j, data->a.size - i + j);
	if (i != 0 && *key <= new)
		return ;
	*key = new;
	if (new == max(i, j))
		return (assign_rotates(rotates, i, j));
	if (new == max(data->a.size - i, data->b.size - j))
		return (assign_rotates(rotates, i - data->a.size, j - data->b.size));
	if (new == i + data->b.size - j)
		return (assign_rotates(rotates, i, j - data->b.size));
	if (new == data->a.size - i + j)
		return (assign_rotates(rotates, i - data->a.size, j));
}

void	push_sorted_elem(t_data *data, int rotates[2])
{
	while (rotates[0] || rotates[1])
	{
		if (rotates[0] > 0 && rotates[1] > 0)
			rotate(data, "r");
		else if (rotates[0] < 0 && rotates[1] < 0)
			rotate(data, "rr");
		else
		{
			if (rotates[0] > 0)
				rotate(data, "a");
			if (rotates[1] > 0)
				rotate(data, "b");
			if (rotates[0] < 0)
				rotate(data, "ra");
			if (rotates[1] < 0)
				rotate(data, "rb");
		}
		rotates[0] -= (rotates[0] > 0) - (rotates[0] < 0);
		rotates[1] -= (rotates[1] > 0) - (rotates[1] < 0);
	}
	push(data, 'b');
}

void	greedy_sort(t_data *data)
{
	int		i;
	int		key;
	int		rotates[2];

	if (data->a.size > 3)
	{
		push(data, 'b');
		push(data, 'b');
	}
	while (data->a.size > 3)
	{
		i = -1;
		while (++i < data->a.size)
			count_rotates(data, i, &key, rotates);
		push_sorted_elem(data, rotates);
	}
	sort_a_under_3(data);
	rotates[0] = count_position(data, (long)INT32_MAX + 1);
	if (rotates[0] <= data->b.size / 2)
		while ((rotates[0])-- > 0)
			rotate(data, "b");
	else
		while ((rotates[0])++ < data->b.size)
			rotate(data, "rb");
	push_back_to_a(data);
}
