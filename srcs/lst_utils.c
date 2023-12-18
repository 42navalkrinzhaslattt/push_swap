/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nam-vu <nam-vu@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:56:14 by nam-vu            #+#    #+#             */
/*   Updated: 2023/12/18 19:56:14 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/push_swap.h"
#include "push_swap.h"

t_list	*ft_lstnew(int value)
{
	t_list	*res;

	res = malloc(sizeof(*res) * 1);
	if (!res)
		return (NULL);
	res->value = value;
	res->next = NULL;
	return (res);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!(*lst))
		*lst = new;
	else
	{
		temp = *lst;
		*lst = new;
		(*lst)->next = temp;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*curr;
	t_list	*next;

	if (!lst)
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
