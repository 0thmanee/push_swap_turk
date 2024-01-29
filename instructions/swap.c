/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:13:10 by obouchta          #+#    #+#             */
/*   Updated: 2024/01/20 18:04:00 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(t_node **stack)
{
	t_node	*tmp;
	
	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = (*stack)->next;
	(*stack)->next = tmp;
}

void	sa(t_node **stack, char c)
{
	if (!(*stack) || !(*stack)->next)
		return ;
	swap(stack);
	if (c == 'y')
		return ;
	write(1, "sa\n", 3);
}
void	sb(t_node **stack, char c)
{
	if (!(*stack) || !(*stack)->next)
		return ;
	swap(stack);
	if (c == 'y')
		return ;
	write(1, "sb\n", 3);
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	if ((*stack_a && (*stack_a)->next) || (*stack_b && (*stack_b)->next))
	{
		write(1, "ss\n", 3);
		sa(stack_a, 'y');
		sb(stack_b, 'y');
	}
}