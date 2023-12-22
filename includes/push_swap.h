#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

typedef struct s_list
{
	struct s_list	*next;
	int				value;
}	t_list;

typedef struct s_stack
{
	long	*arr;
	int		start;
	int		size;
}	t_stack;

typedef struct s_data
{
	t_stack	a;
	t_stack	b;
}	t_data;

//push_swap.c
void	init_data(t_data *data, int ac);
int		check_doubles(t_data *data);
void	quick_sort(int *arr, int begin, int end);
int		check_input(char **av, int ac, t_data *data);
int		main(int ac, char **av);

//operations.c
void	swap(t_data *data, char flag);
void	push(t_data *data, char flag);
void	rotate(t_data *data, char *flag);

//utils.c
void	error_exit(t_data *data, int flag);
int		ft_strlen(const char *s);
void	*ft_memmove(void *dest, const void *src, size_t n);

#endif