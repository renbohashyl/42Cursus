/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:12:28 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 22:15:37 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define SUC 1
# define FAIL 0
# define PRT 1
# define NON 0
# define R 1
# define RR 0
# define ERROR -1
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define STDOUT 1
# define STDERR 2
# define WORST 1
# define NORMAL 0

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

//ft_split.c
char	**ft_split(char const *s);
void	*make_free(char **splt);

//push_swap_node_control.c
t_node	*ft_nn(int value);

//push_swap_rules_push_and_rotate.c
int		pa(t_node **a_top, t_node **b_top);
int		pb(t_node **a_top, t_node **b_top);
int		ra(t_node **a_top, int option);
int		rb(t_node **b_top, int option);
int		rr(t_node **a_top, t_node **b_top);

//push_swap_rules_reverse_rotate.c
int		rra(t_node **a_top, int option);
int		rrb(t_node **b_top, int option);
int		rrr(t_node **a_top, t_node **b_top);

//push_swap_rules_swap.c
int		sa(t_node **top, int option);
int		sb(t_node **top, int option);
int		ss(t_node **a_top, t_node **b_top);

//push_swap_sort_a_control.c
void	a_to_b(t_node **a_top, t_node **b_top, int total, int worst_or_not);

//push_swap_sort_b_control.c
void	b_to_a(t_node **a_top, t_node **b_top, int total);

//push_swap_sort.c
void	sort(t_node **a_top, t_node **b_top, int total, int worst_or_not);

//push_swap_stack_control.c
void	push(t_node **top, t_node *arg);
t_node	*pop(t_node **top);
void	push_bottom(t_node **top, t_node *arg);
t_node	*pop_bottom(t_node **top);
int		top(t_node **vtop);

// push_swap_utils_libft.c
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *nptr);
int		ft_issp(int c);
int		ft_isnum(int c);
void	exit_error(void);

//push_swap_utils.c
int		parse_digits(int cnt, char **array, t_node **top);

//push_swap.c
void	r_or_rr(t_node **vtop, int cnt, int option, char stack);
int		search(t_node *vtop, int nbr);

#endif
