/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:23:03 by obouchta          #+#    #+#             */
/*   Updated: 2024/01/24 18:23:20 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*find_cheapest_in_b(t_stack *a, t_stack *b)
{
	t_node	*tmp;
	t_node	*tmp2;
	t_node	*cheap;

	tmp = a->head;
	cheap = tmp;
	while (tmp)
	{
		if (tmp->index <= a->size / 2)
			tmp->cost = tmp->index;
		else
			tmp->cost = a->size - tmp->index + 1;
		tmp2 = b->head;
		tmp->target = tmp;
		while (tmp2)
		{
			if (tmp2->value < tmp->value && tmp->value == tmp->target->value)
				tmp->target = tmp2;
			if (tmp2->value < tmp->value && tmp2->value > tmp->target->value)
				tmp->target = tmp2;
			tmp2 = tmp2->next;
		}
		if (tmp->value != tmp->target->value && tmp->target->index != 1)
		{
			if (tmp->target->index <= b->size / 2)
				tmp->cost += tmp->target->index;
			else
				tmp->cost += (b->size - tmp->target->index + 1);
		}
		else if (tmp->value == tmp->target->value && tmp->index > a->size / 2)
			tmp->cost++;
		if (tmp->cost < cheap->cost)
			cheap = tmp;
		tmp = tmp->next;
	}
	return (cheap);
}

void	rotate_both(t_stack **a, t_stack **b, t_node *cheap)
{
	int		i;
	int		j;
	
	i = cheap->index;
	j = cheap->target->index;
	while (i > 1 && j > 1)
	{
		rr(&(*a)->head, &(*b)->head);
		i--;
		j--;
	}
	while (i > 1)
	{
		ra(&(*a)->head, 'n');
		i--;
	}
	while (j > 1)
	{
		rb(&(*b)->head, 'n');
		j--;
	}
}

void	rrotate_both(t_stack **a, t_stack **b, t_node *cheap)
{
	int		i;
	int		j;
	
	i = (*a)->size - cheap->index + 1;
	j = (*b)->size - cheap->target->index + 1;
	while (i > 0 && j > 0)
	{
		rrr(&(*a)->head, &(*b)->head);
		i--;
		j--;
	}
	while (i > 0)
	{
		rra(&(*a)->head, 'n');
		i--;
	}
	while (j > 0)
	{
		rrb(&(*b)->head, 'n');
		j--;
	}
}

void	ra_rrb(t_stack **a, t_stack **b, t_node *cheap)
{
	int		i;
	
	i = cheap->index;
	while (i > 1)
	{
		ra(&(*a)->head, 'n');
		i--;
	}
	i = (*b)->size - cheap->target->index + 1;
	while (i > 0)
	{
		rrb(&(*b)->head, 'n');
		i--;
	}
}

void	rra_rb(t_stack **a, t_stack **b, t_node *cheap)
{
	int		i;
	i = (*a)->size - cheap->index + 1;
	while (i >  0)
	{
		rra(&(*a)->head, 'a');
		i--;
	}
	i = cheap->target->index;
	while (i > 1)
	{
		rb(&(*b)->head, 'n');
		i--;
	}
}

void	find_place_in_b(t_stack **a, t_stack **b)
{
	t_node	*tmp;
	int		val;
	int		avg;

	tmp = find_cheapest_in_b(*a, *b);
	val = tmp->value;
	if (tmp->value == tmp->target->value)
		rotate_no_target(a, tmp);
	else if (tmp->index <= (*a)->size / 2 && tmp->target->index <= (*b)->size / 2)
		rotate_both(a, b, tmp);
	else if (tmp->index > (*a)->size / 2 && tmp->target->index > (*b)->size / 2)
		rrotate_both(a, b, tmp);
	else if (tmp->index <= (*a)->size / 2 && tmp->target->index > (*b)->size / 2)
		ra_rrb(a, b, tmp);
	else if (tmp->index > (*a)->size / 2 && tmp->target->index <= (*b)->size / 2)
		rra_rb(a, b, tmp);
	index_stack(*a);
	index_stack(*b);
	pb(&(*a)->head, &(*b)->head);
}

void	push_to_b(t_stack **a, t_stack **b)
{
	if (!(*a)->head || !(*a)->head->next)
		return ;
	if (!(*b))
	{
		*b = malloc(sizeof(t_stack));
		if (!*b)
			return ;
	}
	pb(&(*a)->head, &(*b)->head);
	pb(&(*a)->head, &(*b)->head);
	index_stack(*a);
	index_stack(*b);
	// int moy = stack_s_max((*a)->head) + stack_s_min((*a)->head) / 2;
	while ((*a)->size > 3)
	{
		find_place_in_b(a, b);
		index_stack(*a);
		index_stack(*b);
	}
	if ((*a)->size <= 3)
		sort_stack3(a);
	index_stack(*a);
}
