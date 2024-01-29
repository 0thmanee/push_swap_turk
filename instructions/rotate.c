/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:25:16 by obouchta          #+#    #+#             */
/*   Updated: 2024/01/20 18:11:20 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotate(t_node **stack)
{
	t_node	*tmp;
	t_node	*tmp2;
	
	tmp = *stack;
	*stack = (*stack)->next;
	tmp2 = *stack;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
	tmp->next = NULL;
}

void	ra(t_node **stack, char c)
{
	if (!(*stack) || !(*stack)->next)
		return ;
	rotate(stack);
	if (c == 'y')
		return ;
	write(1, "ra\n", 3);
}

void	rb(t_node **stack, char c)
{
	if (!(*stack) || !(*stack)->next)
		return ;
	rotate(stack);
	if (c == 'y')
		return ;
	write(1, "rb\n", 3);
}

void	rr(t_node **stack_a, t_node **stack_b)
{
	if ((*stack_a && (*stack_a)->next) || (*stack_b && (*stack_b)->next))
	{
		ra(stack_a, 'y');
		rb(stack_b, 'y');
		write(1, "rr\n", 3);
	}
}