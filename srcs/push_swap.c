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

//#include "../includes/push_swap.h"
#include "push_swap.h"
void	error_exit(t_data *data, int flag)
{
	int	i;

	if (flag == 1)
		exit(EXIT_SUCCESS);
	i = -1;
	if (data->lst)
		ft_lstclear(&data->lst);
	write (2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	init_data(t_data *data, int ac)
{
	data->lst = NULL;
	data->lst_len = ac - 1;
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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
		ft_lstadd_back(&data->lst, ft_lstnew(value * sign));
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac);
	if (ac == 1)
		error_exit(&data, (ac == 1));
	if (!check_input(av, ac, &data))
		error_exit(&data, 0);
	write(1, "OK\n", 3);
	ft_lstclear(&data.lst);
}
