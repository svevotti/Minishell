# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 14:49:17 by jbeck             #+#    #+#              #
#    Updated: 2024/03/04 15:40:35 by jbeck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror -g -I ./includes/

LIBFT	:= ./libft

LKLIBFT	:= -L $(LIBFT) -lft

LIBS	:= $(LKLIBFT) -lreadline

SRCS	:=	./src/main.c \
			./src/handle_env_var.c \
			./src/trans_env.c \
			./src/split_input.c \
			./src/check_first_argv.c \
			./src/free_functions.c \
			./src/find_size_env_var.c \
			./src/utils_env_var.c \
			./src/print_array.c \
			./src/size_split_input.c \
			./src/utilis_trans_env.c \
			./src/exec.c \
			./src/parse_cmds.c \
			./src/executor.c \
			./src/builtin.c \
			./src/redirection.c \
			./src/heredoc.c \
			./src/error.c \
			./src/minishell.c \
			./src/free.c \
			./src/tools.c \
			./src/craete_input_pipes_end.c \
			./src/error_messages.c
			
OBJS	:= ${SRCS:.c=.o}

all: libft $(NAME)

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME) && printf "Compiling: $(NAME)\n"

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean	
	
re: fclean all

.PHONY: all clean fclean re libft