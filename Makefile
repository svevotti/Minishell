# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 14:49:17 by jbeck             #+#    #+#              #
#    Updated: 2024/03/21 11:24:49 by jbeck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CC		:= cc

CFLAGS	:= -Wextra -Wall -Werror -g -I ./includes/

LIBFT	:= ./libft

LKLIBFT	:= -L $(LIBFT) -lft

LIBS	:= $(LKLIBFT) -lreadline
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
			./src/check_path.c \
			./src/initialize_program.c \
			./src/split_input_utils.c \
			./src/builtins/ft_echo.c \
			./src/builtins/ft_env.c \
			./src/builtins/ft_export.c \
			./src/builtins/ft_pwd.c \
			./src/builtins/ft_unset.c \
			./src/builtins/ft_cd.c \
			./src/builtins/ft_exit.c \
			./src/split_processes.c \
			./src/error_syntax_pipes.c \
			./src/remove_quotes.c \
			./src/prepare_redirections.c \
			./src/split_input_utils2.c \
			./src/handle_env_var_utils.c \
			./src/check_redirection.c \
			./src/remove_quotes_utils.c \
			./src/signals.c \
			./src/check_next_file.c
      
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