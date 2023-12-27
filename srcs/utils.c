/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:36:37 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/22 16:36:37 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
//#include "../includes/push_swap.h"

void	error_exit(t_data *data, int flag)
{
	if (flag == 1)
		exit(EXIT_SUCCESS);
	if (data->a.arr)
		free(data->a.arr);
	if (data->b.arr)
		free(data->b.arr);
	write (2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	ssize_t	i;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		i = 0;
		while (i < (ssize_t)n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n - 1;
		while (i >= 0)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	return (dest);
}

int	is_sorted(t_stack stack)
{
	int	i;

	i = 0;
	while (i < stack.size - 1)
	{
		if (stack.arr[(stack.start + i) % stack.size]
			> stack.arr[(stack.start + i + 1) % stack.size])
			return (0);
		i++;
	}
	return (1);
}

void	stack_align(t_data *data)
{
	if (data->a.size > 1)
		while (data->a.arr[data->a.start]
			> data->a.arr[(data->a.start + data->a.size - 1) % data->a.size])
			rotate(data, "a");
	if (data->b.size > 1)
		while (data->b.arr[data->b.start]
			> data->b.arr[(data->b.start + data->b.size - 1) % data->b.size])
			rotate(data, "b");
}
