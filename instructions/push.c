/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:24:14 by obouchta          #+#    #+#             */
/*   Updated: 2024/01/22 09:50:21 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push(t_node **stack_a, t_node **stack_b)
{
	t_node	*tmp;

	if (!(*stack_b))
		return ;
	tmp = *stack_b;
	*stack_b = (*stack_b)->next;
	tmp->next = *stack_a;
	*stack_a = tmp;
}

void	pa(t_node **stack_a, t_node **stack_b)
{
	if (!(*stack_b))
		return ;
	push(stack_a, stack_b);
	write(1, "pa\n", 3);
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	if (!(*stack_a))
		return ;
	push(stack_b, stack_a);
	write(1, "pb\n", 3);
}
