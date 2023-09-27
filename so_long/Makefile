# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 16:40:12 by jbak              #+#    #+#              #
#    Updated: 2022/08/12 16:17:12 by jbak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long
NAME_BONUS	= so_long_bonus

SRCS		= so_long.c		\
			  valid_check.c	\
			  init.c		\
			  events.c		\
			  freeit.c		\
			  getimgs.c

SRCB		= so_long_bonus.c		\
			  valid_check_bonus.c	\
			  init_bonus.c			\
			  events_bonus.c		\
			  freeit_bonus.c		\
			  getimgs_bonus.c

OBJS		= $(addprefix $(OBJDIR),$(SRCS:.c=.o))
OBJB		= $(addprefix $(OBJDIR_B),$(SRCB:.c=.o))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3

#libft
LIBFT		= ./libfts
LIBFT_LIB	= $(addprefix $(LIBFT)/,libft.a)
LIBFT_INC	= -I $(LIBFT)/
LIBFT_LNK	= -L $(LIBFT)/ -l ft

#mlx
MLX			= ./minilibx-Macos
MLX_LIB		= $(addprefix $(MLX)/,libmlx.a)
MLX_INC		= -I $(MLX)/
MLX_LNK		= -L $(MLX) -l mlx -framework OpenGL -framework AppKit#-lm -lXext -lX11

#dirs
SRCDIR		= ./src/
SRCDIR_B	= ./bonus/src_bonus/
INCDIR		= -I ./inc/
INCDIR_B	= -I ./bonus/inc_bonus/
OBJDIR		= ./obj/
OBJDIR_B	= ./bonus/obj/

all : $(OBJDIR) $(MLX_LIB) $(LIBFT_LIB) $(NAME)
bonus : $(OBJDIR_B) $(MLX_LIB) $(LIBFT_LIB) $(NAME_BONUS)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR_B) :
	mkdir -p $(OBJDIR_B)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(LIBFT_INC) $(MLX_INC) $(INCDIR) -o $@ -c $<

$(OBJDIR_B)%.o : $(SRCDIR_B)%.c
	$(CC) $(CFLAGS) $(LIBFT_INC) $(MLX_INC) $(INCDIR_B) -o $@ -c $<

$(LIBFT_LIB) :
	make -sC $(LIBFT)

$(MLX_LIB) :
	make -sC $(MLX)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LNK) $(MLX_LNK) -o $(NAME)

$(NAME_BONUS) : $(OBJB)
	$(CC) $(CFLAGS) $(OBJB) $(LIBFT_LNK) $(MLX_LNK) -o ./bonus/$(NAME_BONUS)

clean :
	rm -rf $(OBJDIR)
	rm -rf $(OBJDIR_B)
	make -sC $(LIBFT)/ clean
	make -sC $(MLX) clean

fclean : clean
	rm -f $(NAME)
	rm -rf $(NAME_BONUS)
	rm -f $(addprefix $(MLX)/,libmlx.a)
	make -sC $(LIBFT) fclean

re : fclean all

.PHONY : clean fclean re all bonus