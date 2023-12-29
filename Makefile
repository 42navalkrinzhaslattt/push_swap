NAME	= push_swap

BONUS_NAME	= checker

PUSH_SWAP_SRC	= push_swap/push_swap.c  push_swap/greedy_sort.c push_swap/greedy_sort_utils.c

SHARED_SRC	= shared/check_input.c shared/operations.c shared/utils.c

BONUS_SRC	= checker/checker.c checker/get_next_line.c checker/get_next_line_utils.c

SRC_DIR	= srcs/

OBJ	= $(addprefix $(SRC_DIR), $(PUSH_SWAP_SRC:.c=.o) $(SHARED_SRC:.c=.o))

BONUS_OBJ	= $(addprefix $(SRC_DIR), $(BONUS_SRC:.c=.o) $(SHARED_SRC:.c=.o))

CC		= cc

CFLAGS	= -Wall -Werror -Wextra

%.o: %.c
	$(CC) $(CFLAGS) -I ./includes -c  $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -fsanitize=address -g -o $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -fsanitize=address -g -o $(BONUS_NAME)

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re:	fclean all

.PHONY: all clean fclean re