NAME		= minishell

SRCS		= minishell.c							\
			  base_env_to_list.c					\
			  base_list_to_envp.c					\
			  base_mergesort_for_linked_list.c		\
			  builtin_cd.c							\
			  builtin_echo.c						\
			  builtin_export.c						\
			  builtin_pwd.c							\
			  builtin_unset.c						\
			  builtin_env.c							\
			  builtin_exit.c						\
			  dollar.c								\
			  executor_utils_convert.c				\
			  executor_utils_exec.c					\
			  executor_utils_paths.c				\
			  executor.c							\
			  expand.c								\
			  free.c								\
			  lexer.c								\
			  node.c								\
			  open_heredoc.c						\
			  parser.c								\
			  scanner.c								\
			  scanner_util.c						\
			  search_env.c							\
			  source.c								\
			  signal.c								\
			  token.c								\
			  word.c

OBJS		= $(addprefix $(OBJDIR),$(SRCS:.c=.o))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror $(DBGFLAG)
DBGFLAG		= -g3
LEAKFLAG	= -fsanitize=address

#libft
LIBFT		= ./libft
LIBFT_LIB	= $(addprefix $(LIBFT)/,libft.a)
LIBFT_INC	= -I $(LIBFT)/
LIBFT_LNK	= -L $(LIBFT)/ -l ft

#readline
RDLINE_INC	= -I/$(HOME)/.brew/opt/readline/include 
RDLINE_LNK	= -L$(HOME)/.brew/opt/readline/lib -lreadline

#dirs
SRCDIR		= ./src/
INCDIR		= -I ./inc/
OBJDIR		= ./obj/

all : $(OBJDIR) $(LIBFT_LIB) $(NAME)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(INCDIR) $(LIBFT_INC) $(RDLINE_INC) -c $< -o $@

$(LIBFT_LIB) :
	make -sC $(LIBFT)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LNK) $(RDLINE_INC) $(RDLINE_LNK) -o $(NAME)

clean :
	rm -rf $(OBJDIR)
	make -sC $(LIBFT) clean

fclean : clean
	rm -f $(NAME)
	make -sC $(LIBFT) fclean

re : fclean all

.PHONY : clean fclean re all