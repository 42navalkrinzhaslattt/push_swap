#include "push_swap.h"
//#include "../includes/push_swap.h"

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

void	count_runs_len(t_data *data)
{
	data->b.run = 1;
	if (data->b.size > 1)
		while (data->b.arr[(data->b.start + data->b.run - 1) % data->b.size]
			< data->b.arr[(data->b.start + data->b.run) % data->b.size])
			data->b.run++;
	data->a.run = 1;
	if (data->a.size > 1)
		while (data->a.arr[(data->a.start + data->a.run - 1) % data->a.size]
			< data->a.arr[(data->a.start + data->a.run) % data->a.size])
			data->a.run++;
	if (data->a.size <= 1)
		data->a.run = data->a.size;
	if (data->b.size <= 1)
		data->b.run = data->b.size;
}

void	merge_to_b(t_data *data)
{
	count_runs_len(data);
	while (data->a.run || data->b.run)
	{
		if ((data->b.arr[data->b.start] < data->a.arr[data->a.start]
			&& data->b.run) || !data->a.run)
		{
			rotate(data, "b");
			data->b.run--;
		}
		else
		{
			push(data, 'b');
			rotate(data, "b");
			data->a.run--;
		}
	}
}

void	merge_to_a(t_data *data)
{
	count_runs_len(data);
	while (data->b.run || data->a.run)
	{
		if ((data->a.arr[data->a.start] < data->b.arr[data->b.start]
			 && data->a.run) || !data->b.run)
		{
			rotate(data, "a");
			data->a.run--;
		}
		else
		{
			push(data, 'a');
			rotate(data, "a");
			data->b.run--;
		}
	}
}

void	split_runs(t_data *data, int *counter)
{
	long	last;

	rotate(data, "a");
	if (--(*counter) == 0)
		return ;
	while (data->a.arr[data->a.start]
		> data->a.arr[(data->a.start + data->a.size - 1) % data->a.size])
	{
		rotate(data, "a");
		if (--(*counter) == 0)
			return ;
	}
	last = data->a.arr[data->a.start];
	push(data, 'b');
	rotate(data, "b");
	if (--(*counter) == 0)
		return ;
	while (data->a.arr[data->a.start] > last)
	{
		last = data->a.arr[data->a.start];
		push(data, 'b');
		rotate(data, "b");
		if (--(*counter) == 0)
			return ;
	}
}

void	merge_sort(t_data *data) //need optimization(merge runs in A beforehand), for small cases exceptionally
{
	int		counter;
	int		flag;

	stack_align(data);
//	rotate(data, "a");
//	rotate(data, "a");
//	rotate(data, "a");
//	push(data, 'b');
//	rotate(data, "b");
//	push(data, 'b');
//	rotate(data, "b");
//	push(data, 'b');
//	rotate(data, "b");
//	rotate(data, "a");
//	rotate(data, "a");
//	rotate(data, "a");
//	push(data, 'b');
//	rotate(data, "b");
//	push(data, 'b');
//	rotate(data, "b");
//	push(data, 'b');
//	rotate(data, "b");
	while ((data->b.size != 0 || !is_sorted(data->a))
		&& (data->a.size != 0 || !is_sorted(data->b)))
	{
		if (data->b.size == 0)
		{
			counter = data->a.size;
			while (counter > 0)
				split_runs(data, &counter);
		}
		count_runs_len(data);
		flag = data->a.run >= data->b.run;
		if (flag)
			merge_to_a(data);
		merge_to_b(data);
		if (!flag)
			merge_to_a(data);
		stack_align(data);
	}
	count_runs_len(data);
	if (data->a.size == 0)
		merge_to_a(data);
}
