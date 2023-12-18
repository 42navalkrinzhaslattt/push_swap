NAME	= push_swap

SRC		= push_swap.c lst_utils.c

BONUS_SRC		= so_long_bonus.c input_check_bonus.c utils_bonus.c hooks_bonus.c render_bonus.c

SRC_DIR	= srcs/

BONUS_SRC_DIR	= srcs_bonus/

OBJ	= $(addprefix $(SRC_DIR), $(SRC:.c=.o))

BONUS_OBJ	= $(addprefix $(BONUS_SRC_DIR), $(BONUS_SRC:.c=.o))

CC		= cc

CFLAGS	= -Wall -Werror -Wextra

%.o: %.c
	$(CC) $(CFLAGS) -I ./includes -c  $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -fsanitize=address -g -o $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -fsanitize=address -g -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re