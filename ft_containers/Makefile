NAME		= ft_containers

SRCS		= main.cpp

OBJS		= $(addprefix $(OBJDIR),$(SRCS:.cpp=.o))

CXX			= c++
CXXFLAG		= -Wall -Wextra -Werror -std=c++98
DBGFLAG		= -g3
ADRFLAG		= -fsanitize=address
DEFINE_FLAG = ft
ifdef std
 DEFINE_FLAG = _use_std
endif

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
	$(CXX) $(CXXFLAG) -D $(DEFINE_FLAG) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re all std
