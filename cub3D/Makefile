NAME		= cub3d

SRCS		= cubd.c				\
			  initialize.c			\
			  key_event.c			\
			  parsing.c				\
			  raycast_calc_utils.c	\
			  raycast_calc.c		\
			  valid_check.c			\
			  valid_check_utils.c

OBJS		= $(addprefix $(OBJDIR),$(SRCS:.c=.o))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror $(DBGFLAG)
DBGFLAG		= -g3
HEAPFLAG	= -fsanitize=address

#libft
LIBFT		= ./libft/
LIBFT_LIB	= $(addprefix $(LIBFT),libft.a)
LIBFT_INC	= -I $(LIBFT)
LIBFT_LNK	= -L $(LIBFT) -l ft

#mlx
MLX			= ./minilibx_opengl_20191021/
MLX_LIB		= $(addprefix $(MLX),libmlx.a)
MLX_INC		= -I $(MLX)
MLX_LNK     = -L $(MLX) -l mlx -framework OpenGL -framework AppKit

#dirs
SRCDIR		= ./src/
INCDIR		= -I ./inc/
OBJDIR		= ./obj/

all : $(OBJDIR) $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(OBJDIR) :
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(INCDIR) $(MLX_INC) $(LIBFT_INC) -c $< -o $@

$(LIBFT_LIB) :
	@make -sC $(LIBFT)

$(MLX_LIB) :
	@make -sC $(MLX)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LNK) $(MLX_LNK) -o $(NAME)

clean :
	@rm -rf $(OBJDIR)
	@make -sC $(LIBFT) clean
	@make -sC $(MLX) clean

fclean : clean
	@rm -f $(NAME)
	@rm -f $(MLX_LIB)
	@make -sC $(LIBFT) fclean

re : fclean all

.PHONY : clean fclean re all