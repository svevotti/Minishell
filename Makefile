# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbeck <jbeck@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 14:49:17 by jbeck             #+#    #+#              #
#    Updated: 2024/02/08 12:38:17 by jbeck            ###   ########.fr        #
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
			./src/find_size_env_var.c
			
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