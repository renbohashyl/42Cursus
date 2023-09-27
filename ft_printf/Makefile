NAME		= libftprintf.a

INC			= ./ft_printf.h

SRCS		= ft_printf.c					\
			  ft_printf_utils_characters.c	\
			  ft_printf_utils_numbers.c

OBJS		= $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

$(NAME) : $(OBJS)
	ar crs $@ $^

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean all
