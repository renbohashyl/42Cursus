# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 17:38:12 by jbak              #+#    #+#              #
#    Updated: 2022/06/06 19:57:00 by jbak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap
BNS			= checker

INC			= push_swap.h
BNINC		= checker.h

SRCS		= ft_split.c						\
			  push_swap.c						\
			  push_swap_node_control.c			\
			  push_swap_rules_push_and_rotate.c	\
			  push_swap_rules_reverse_rotate.c	\
			  push_swap_rules_swap.c			\
			  push_swap_sort.c					\
			  push_swap_sort_a_control.c		\
			  push_swap_sort_b_control.c		\
			  push_swap_stack_control.c			\
			  push_swap_utils.c					\
			  push_swap_utils_libft.c

SRCS_BN		= checker.c					\
			  checker_doing.c			\
			  checker_utils.c			\
			  checker_utils_libft.c		\
			  checker_gnl.c				\
			  checker_gnl_utils.c		\
			  checker_stack_control.c	\
			  checker_ft_split.c

OBJS		= $(SRCS:.c=.o)
OBJS_BN		= $(SRCS_BN:.c=.o)

all : $(NAME)
bonus : $(BNS)

%.o : %.c
	gcc -Wall -Wextra -Werror -g -c $< -o $@

$(BNS) : $(OBJS_BN)
	gcc -Wall -Wextra -Werror -g $(OBJS_BN) -o $(BNS)

$(NAME) : $(OBJS)
	gcc -Wall -Wextra -Werror -g  $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS) $(OBJS_BN)

fclean : clean
	rm -f $(NAME) $(BNS)

re : fclean all bonus

.PHONY : all clean fclean all
