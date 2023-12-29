/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:08:59 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/29 17:08:59 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putnbr(long n, int flag)
{
	long	nb;
	char	digit;

	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr(nb / 10, 0);
	digit = nb % 10 + 48;
	write(1, &digit, 1);
	if (flag == 1)
		write(1, "\n", 1);
}

int	execute_cmd(t_data *data, char *cmd)
{
	if (!ft_strncmp(cmd, "sa\n", 4))
		swap(data, 'a');
	else if (!ft_strncmp(cmd, "sb\n", 4))
		swap(data, 'b');
	else if (!ft_strncmp(cmd, "ss\n", 4))
		swap(data, 's');
	else if (!ft_strncmp(cmd, "pa\n", 4))
		push(data, 'a');
	else if (!ft_strncmp(cmd, "pb\n", 4))
		push(data, 'b');
	else if (!ft_strncmp(cmd, "ra\n", 4))
		rotate(data, "a");
	else if (!ft_strncmp(cmd, "rb\n", 4))
		rotate(data, "b");
	else if (!ft_strncmp(cmd, "rr\n", 4))
		rotate(data, "r");
	else if (!ft_strncmp(cmd, "rra\n", 5))
		rotate(data, "ra");
	else if (!ft_strncmp(cmd, "rrb\n", 5))
		rotate(data, "rb");
	else if (!ft_strncmp(cmd, "rrr\n", 5))
		rotate(data, "rr");
	else
		return (0);
	return (1);
}

void	print_stacks(t_data *data)
{
	int		i;
	int		j;

	write(1, "stack A:\n", 9);
	i = data->a.start - 1;
	j = -1;
	if (data->a.size > 0)
		while (++j < data->a.size)
			ft_putnbr(data->a.arr[++i % data->a.size], 1);
	write(1, "stack B:\n", 9);
	i = data->b.start - 1;
	j = -1;
	if (data->b.size > 0)
		while (++j < data->b.size)
			ft_putnbr(data->b.arr[++i % data->b.size], 1);
	if (data->b.size == 0 && is_sorted(data->a))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free(data->a.arr);
	free(data->b.arr);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	*cmd;

	init_data(&data, ac);
	if (ac == 1)
		error_exit(&data, 1);
	if (!check_input(av, ac, &data) || !check_doubles(&data))
		error_exit(&data, 0);
	cmd = get_next_line(0);
	while (cmd)
	{
		write(1, "Executing: ", 11);
		if (!execute_cmd(&data, cmd))
		{
			free(cmd);
			error_exit(&data, 0);
		}
		free(cmd);
		cmd = get_next_line(0);
	}
	print_stacks(&data);
}
