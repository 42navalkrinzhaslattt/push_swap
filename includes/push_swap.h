#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_list
{
	struct s_list	*next;
	int				value;
}	t_list;

typedef struct s_data
{
	t_list	*lst;
	int		lst_len;
}	t_data;

//push_swap.c
void	error_exit(t_data *data, int flag);
void	init_data(t_data *data, int ac);
int		ft_strlen(const char *s);
int		check_input(char **av, int ac, t_data *data);
int		main(int ac, char **av);
//lst_utils.c
t_list	*ft_lstnew(int value);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);


#endif