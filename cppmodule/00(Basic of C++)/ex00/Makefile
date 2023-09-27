# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 18:28:02 by jbak              #+#    #+#              #
#    Updated: 2022/12/16 18:28:07 by jbak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= megaphone

SRCS		= megaphone.cpp

OBJS		= $(addprefix $(OBJDIR),$(SRCS:.cpp=.o))

COMPILER	= c++
COMPILEFLAG	= -Wall -Wextra -Werror -std=c++98 $(DBGFLAG)
DBGFLAG		= -g3 
LEAKFLAG	= -fsanitize=address

#dirs
SRCDIR		= ./
INCDIR		= -I ./
OBJDIR		= ./obj/

all : $(OBJDIR) $(NAME)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(COMPILER) $(COMPILEFLAG) $(INCDIR) -o $@ -c $<

$(NAME) : $(OBJS)
	$(COMPILER) $(COMPILEFLAG) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re all
