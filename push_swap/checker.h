/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:42:56 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 20:11:35 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# define SUC 1
# define FAIL 0
# define ERROR -1
# define RR 0
# define RRR 1
# define SS 2
# define BUFFER_SIZE 3
# define INT_MAX 2147483647
# define INT_MIN -214748368
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# include <unistd.h>
# include <stdlib.h>

typedef struct s_node
{
	struct s_node	*next;
	int				value;
	int				index;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
}	t_stack;

//checker_doing.c
void	doit(char *cmd, t_node **a_top, t_node **b_top);

//checker_ft_split.c
char	**ft_split(char const *s);
void	*make_free(char **splt);

//checker_gnl_utils.c
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);

//checker_gnl.c
char	*get_next_line(int fd);

//checker_stack_control.c
void	push(t_node **top, t_node *arg);
t_node	*pop(t_node **top);
void	push_bottom(t_node **top, t_node *arg);
t_node	*pop_bottom(t_node **top);
int		top(t_node **vtop);

//checker_utils_libft.c
void	exit_error(void);
int		ft_issp(int c);
int		ft_isnum(int c);
int		ft_atoi(const char *nptr);

//checker_utils.c
void	parse_digits(int cnt, char **array, t_node **top);
t_node	*ft_nn(int value);

#endif
