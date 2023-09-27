# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 16:40:12 by jbak              #+#    #+#              #
#    Updated: 2022/08/29 16:19:14 by jbak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRCS		= philosopher.c	\
			  ftfunctions.c	\
			  behavior.c	\
			  utils.c		\

OBJS		= $(addprefix $(OBJDIR),$(SRCS:.c=.o))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
THREADFLAG	= -g3 -pthread -fsanitize=thread
LEAKFLAG	= -g3 -fsanitize=address

#libft
#LIBFT		= ./libft
#LIBFT_LIB	= $(addprefix $(LIBFT)/,libft.a)
#LIBFT_INC	= -I $(LIBFT)/
#LIBFT_LNK	= -L $(LIBFT)/ -l ft

#dirs
SRCDIR		= ./src/
INCDIR		= -I ./inc/
OBJDIR		= ./obj/

all : $(OBJDIR) $(NAME)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(INCDIR) -o $@ -c $<

$(LIBFT_LIB) :
	make -sC $(LIBFT)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re all testleak testthread
