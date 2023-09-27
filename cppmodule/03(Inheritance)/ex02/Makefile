# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbak <jbak@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/22 14:59:36 by jbak              #+#    #+#              #
#    Updated: 2023/01/04 21:25:45 by jbak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Repetitivework

SRCS		= main.cpp		\
			  ClapTrap.cpp	\
			  ScavTrap.cpp	\
			  FragTrap.cpp

OBJS		= $(addprefix $(OBJDIR),$(SRCS:.cpp=.o))

CXX			= c++
CXXFLAG		= -Wall -Wextra -Werror -std=c++98 $(DBGFLAG)
DBGFLAG		= -g3
LEAKFLAG	= -fsanitize=address

#dirs
SRCDIR		= ./src/
INCDIR		= -I ./inc/
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
