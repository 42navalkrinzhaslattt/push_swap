#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

typedef struct s_stack
{
	long	*arr;
	int		start;
	int		size;
	int		run;
}	t_stack;

typedef struct s_data
{
	t_stack	a;
	t_stack	b;
}	t_data;

//merge_sort.c
void	stack_align(t_data *data);
void	count_runs_len(t_data *data);
void	merge_to_b(t_data *data);
void	merge_to_a(t_data *data);
void	split_runs(t_data *data, int *counter);
void	merge_sort(t_data *data);

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
int		is_sorted(t_stack stack);

#endif