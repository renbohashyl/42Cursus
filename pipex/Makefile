# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 16:40:12 by jbak              #+#    #+#              #
#    Updated: 2022/09/14 20:01:55 by jbak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
NAME_BONUS	= pipex_bonus

SRCS		= pipex.c		\
			  ft_split.c	\
			  utils.c

SRCB		= pipex_bonus.c		\
			  here_doc_bonus.c	\
			  utils_bonus.c		\
			  utils2_bonus.c	\
			  utils3_bonus.c	\
			  utils4_bonus.c

OBJS		= $(addprefix $(OBJDIR),$(SRCS:.c=.o))
OBJS_BNS	= $(addprefix $(OBJDIR),$(SRCB:.c=.o))

COMPILER	= cc
COMPILEFLAG	= -Wall -Wextra -Werror
DBGFLAG		= -g3 
LEAKFLAG	= -fsanitize=address

#dirs
SRCDIR		= ./src/
SRCBDIR		= ./bonus/
INCDIR		= -I ./inc/
OBJDIR		= ./obj/

all : $(OBJDIR) $(NAME)
bonus : $(OBJDIR) $(NAME_BONUS)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(COMPILER) $(COMPILEFLAG) $(INCDIR) -o $@ -c $<

$(OBJDIR)%.o : $(SRCBDIR)%.c
	$(COMPILER) $(COMPILEFLAG) $(INCDIR) $(DBGFLAG) -o $@ -c $<

$(NAME) : $(OBJS)
	$(COMPILER) $(COMPILEFLAG) $(OBJS) -o $(NAME)

$(NAME_BONUS) : $(OBJS_BNS)
	$(COMPILER) $(COMPILEFLAG) $(OBJS_BNS) $(DBGFLAG) -o $(NAME_BONUS)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re : fclean all

.PHONY : clean fclean re all testleak testthread
