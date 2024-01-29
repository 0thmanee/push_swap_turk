/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:56:50 by obouchta          #+#    #+#             */
/*   Updated: 2024/01/24 18:10:23 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

typedef struct s_node
{
	int				value;
	int				index;
	int				cost;
	struct s_node	*next;
	struct s_node	*target;
}					t_node;

typedef struct s_stack
{
	t_node	*head;
	int		size;
} t_stack;


size_t	ft_strlen(const char *s);
long	calc_result(long tmp, long result, char c, int sign);
long	ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		valid_args(int ac, char *av[], t_stack **a);
void	index_stack(t_stack *stack);
void	sa(t_node **stack, char c);
void	sb(t_node **stack, char c);
void	ss(t_node **stack_a, t_node **stack_b);
void	pa(t_node **stack_a, t_node **stack_b);
void	pb(t_node **stack_a, t_node **stack_b);
void	ra(t_node **stack, char c);
void	rb(t_node **stack, char c);
void	rr(t_node **stack_a, t_node **stack_b);
void	rra(t_node **stack, char c);
void	rrb(t_node **stack, char c);
void	rrr(t_node **stack_a, t_node **stack_b);
void    print_stack1(t_stack *stack, char *name);
void    print_stack2(t_stack *stack, char *name);
int		stack_sorted(t_node *stack);
void 	ft_free_nodes(t_stack **stack);
int		stack_s_max(t_node *stack);
int		stack_s_min(t_node *stack);
void	sort_stack3(t_stack **stack);
void	free_nodes(t_node **node);
void	rotate_no_target(t_stack **stack, t_node *cheap);
t_node	*find_cheapest_in_b(t_stack *a, t_stack *b);
void	rotate_both(t_stack **a, t_stack **b, t_node *cheap);
void	rrotate_both(t_stack **a, t_stack **b, t_node *cheap);
void	ra_rrb(t_stack **a, t_stack **b, t_node *cheap);
void	rra_rb(t_stack **a, t_stack **b, t_node *cheap);
void	find_place_in_b(t_stack **a, t_stack **b);
void	push_to_b(t_stack **a, t_stack **b);

#endif