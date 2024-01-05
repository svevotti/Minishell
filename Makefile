CC = cc
FLAGS = -Werror -Wextra -Wall
NAME = minishell
MINISHELL_FILES = main.c ft_split.c
MINISHELL_OBJ = $(MINISHELL_FILES:.c=.o)

all: $(NAME)

$(NAME): $(MINISHELL_OBJ)
		$(CC) $(FLAGS) $(MINISHELL_OBJ) -o $(NAME) -lreadline

%.o: %.c
	$(CC) -c $^

clean:
		rm -f $(MINISHELL_OBJ)
fclean: clean
		rm -f $(NAME)
re: fclean all
.PHONY: clean fclean re all
