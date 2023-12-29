/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:50:48 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/29 15:50:48 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "shared.h"

//greedy_sort_utils.c
int		max(int a, int b);
int		min(int a, int b, int c, int d);
void	assign_rotates(int rotates[2], int value_0, int value_1);
void	sort_a_under_3(t_data *data);
void	push_back_to_a(t_data *data);

//greedy_sort.c
int		count_position(t_data *data, long nb);
void	count_rotates(t_data *data, int i, int *key, int rotates[2]);
void	push_sorted_elem(t_data *data, int rotates[2]);
void	greedy_sort(t_data *data);

//push_swap.c
int		main(int ac, char **av);

#endif