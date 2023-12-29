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

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac);
	if (ac == 1)
		error_exit(&data, 1);
	if (!check_input(av, ac, &data) || !check_doubles(&data))
		error_exit(&data, 0);
	if (!is_sorted(data.a))
		greedy_sort(&data);
	free(data.a.arr);
	free(data.b.arr);
}
