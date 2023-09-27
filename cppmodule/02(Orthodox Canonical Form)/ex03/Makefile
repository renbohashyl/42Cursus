# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbak <jbak@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 17:01:41 by jbak              #+#    #+#              #
#    Updated: 2022/12/29 19:09:39 by jbak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= BSP

SRCS		= main.cpp	\
			  Fixed.cpp	\
			  Point.cpp	\
			  bsp.cpp

OBJS		= $(addprefix $(OBJDIR),$(SRCS:.cpp=.o))

CXX			= c++
CXXFLAG		= -Wall -Wextra -Werror -std=c++98 $(DBGFLAG)
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
	$(CXX) $(CXXFLAG) $(INCDIR) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAG) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re all
