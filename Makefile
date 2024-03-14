# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 14:49:17 by jbeck             #+#    #+#              #
#    Updated: 2024/03/14 09:35:33 by jbeck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror -g -I ./includes/ -I/opt/homebrew/opt/readline/include

LIBFT	:= ./libft

LKLIBFT	:= -L $(LIBFT) -lft

LIBS	:= $(LKLIBFT) -L/opt/homebrew/opt/readline/lib -lreadline
SRCS	:=	./src/main.c \
			./src/handle_env_var.c \
			./src/trans_env.c \
			./src/split_input.c \
			./src/find_size_env_var.c \
			./src/utils_env_var.c \
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
			./src/error_message_tokens.c \
			./src/error_message_tokens_utils.c \
			./src/initialize_program.c \
			./src/split_input_utils.c \
			./src/check_pipes_syntax.c \
			./src/builtins/ft_echo.c \
			./src/builtins/ft_env.c \
			./src/builtins/ft_export.c \
			./src/builtins/ft_pwd.c \
			./src/builtins/ft_unset.c \
			./src/builtins/ft_cd.c \
			./src/builtins/ft_exit.c \
			
OBJS	:= ${SRCS:.c=.o}

all: libft $(NAME)

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME) && printf "Compiling: $(NAME)\n"

clean:
	@rm -rf $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean	
	
re: fclean all

.PHONY: all clean fclean re libft