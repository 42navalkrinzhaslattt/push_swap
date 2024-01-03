/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:46:57 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/29 15:46:57 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b, int c, int d)
{
	if (a <= b && a <= c && a <= d)
		return (a);
	if (b <= a && b <= c && b <= d)
		return (b);
	if (c <= a && c <= b && c <= d)
		return (c);
	return (d);
}

void	assign_rotates(int rotates[2], int value_0, int value_1)
{
	rotates[0] = value_0;
	rotates[1] = value_1;
}

void	sort_a_under_3(t_data *data)
{
	int	nb[3];

	if (data->a.size > 3 || data->a.size < 2)
		return ;
	if (data->a.size == 2
		&& data->a.arr[data->a.start] > data->a.arr[(data->a.start + 1) % 2])
		swap(data, 'a');
	else
	{
		nb[0] = data->a.arr[data->a.start];
		nb[1] = data->a.arr[(data->a.start + 1) % 3];
		nb[2] = data->a.arr[(data->a.start + 2) % 3];
		if (nb[1] > nb[0] && nb[1] < nb[2])
			return ;
		else if (nb[0] < nb[1] && nb[0] > nb[2])
			rotate(data, "ra");
		else if (nb[2] > nb[1] && nb[2] < nb[0])
			rotate(data, "a");
		else
		{
			swap(data, 'a');
			sort_a_under_3(data);
		}
	}
}

void	push_back_to_a(t_data *data)
{
	int	counter;

	counter = data->a.size;
	while (counter > 0 && data->b.size > 0)
	{
		while (data->b.size > 0 && data->b.arr[data->b.start]
			> data->a.arr[(data->a.start - 1 + data->a.size) % data->a.size])
			push(data, 'a');
		rotate(data, "ra");
		counter--;
	}
	while (data->b.size > 0)
		push(data, 'a');
	if (!is_sorted(data->a))
		while (counter-- > 0)
			rotate(data, "ra");
}
