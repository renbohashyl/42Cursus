NAME		= libft.a

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
DBGFLAG		= -g3

INC			= ./libft.h

SRCS		= ft_atoi.c				\
			  ft_bzero.c			\
			  ft_calloc.c			\
			  ft_memcpy.c			\
			  ft_realloc.c			\
			  ft_split.c			\
			  ft_strchr.c			\
			  ft_strdup.c			\
			  ft_strjoin.c			\
			  ft_strlcpy.c			\
			  ft_strlen.c			\
			  ft_strncmp.c			\
			  ft_strrncmp.c			\
			  ft_substr.c			\
			  get_next_line.c

OBJS		= $(addprefix $(OBJDIR),$(SRCS:.c=.o))

#dirs
SRCDIR		= ./
OBJDIR		= ../obj/libft/

all : $(OBJDIR) $(NAME)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(DBGFLAG) -c $< -o $@

$(NAME) : $(OBJS)
	ar crs $@ $^

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean all
