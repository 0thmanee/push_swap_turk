/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 00:03:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/01/24 18:10:42 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*find_cheapest_in_a(t_stack *a, t_stack *b)
{
	t_node	*tmp;
	t_node	*tmp2;
	t_node	*cheap;

	tmp = b->head;
	cheap = tmp;
	while (tmp)
	{
		if (tmp->index <= b->size / 2)
			tmp->cost = tmp->index;
		else
			tmp->cost = b->size - tmp->index + 1;
		tmp2 = a->head;
		tmp->target = tmp;
		while (tmp2)
		{
			if (tmp2->value > tmp->value && tmp->value == tmp->target->value)
				tmp->target = tmp2;
			if (tmp2->value > tmp->value && tmp2->value < tmp->target->value)
				tmp->target = tmp2;
			tmp2 = tmp2->next;
		}
		if (tmp->value != tmp->target->value && tmp->target->index != 1)
		{
			if (tmp->target->index <= a->size / 2)
				tmp->cost += tmp->target->index;
			else
				tmp->cost += (a->size - tmp->target->index + 1);
		}
		else if (tmp->value == tmp->target->value && tmp->index > b->size / 2)
			tmp->cost++;
		if (tmp->cost < cheap->cost)
			cheap = tmp;
		tmp = tmp->next;
	}
	return (cheap);
}

void	find_cheapest_for_no_targ(t_stack *a, t_stack *b, t_node *tmp)
{
	t_node	*tmp2;

	tmp2 = a->head;
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
		if (tmp->target->index <= a->size / 2)
			tmp->cost += tmp->target->index;
		else
			tmp->cost += (a->size - tmp->target->index + 1);
	}
	else if (tmp->value == tmp->target->value && tmp->index > b->size / 2)
		tmp->cost++;
}

void	rotate_both_2(t_stack **a, t_stack **b, t_node *cheap)
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
		rb(&(*b)->head, 'n');
		i--;
	}
	while (j > 1)
	{
		ra(&(*a)->head, 'n');
		j--;
	}
}

void	rrotate_both_2(t_stack **a, t_stack **b, t_node *cheap)
{
	int		i;
	int		j;
	
	i = (*b)->size - cheap->index + 1;
	j = (*a)->size - cheap->target->index + 1;
	while (i > 0 && j > 0)
	{
		rrr(&(*a)->head, &(*b)->head);
		i--;
		j--;
	}
	while (i > 0)
	{
		rrb(&(*b)->head, 'n');
		i--;
	}
	while (j > 0)
	{
		rra(&(*a)->head, 'n');
		j--;
	}
}

void	rb_rra(t_stack **a, t_stack **b, t_node *cheap)
{
	int		i;
	
	i = cheap->index;
	while (i > 1)
	{
		rb(&(*b)->head, 'n');
		i--;
	}
	i = (*a)->size - cheap->target->index + 1;
	while (i > 0)
	{
		rra(&(*a)->head, 'n');
		i--;
	}
}

void	rrb_ra(t_stack **a, t_stack **b, t_node *cheap)
{
	int		i;
	i = (*b)->size - cheap->index + 1;
	while (i >  0)
	{
		rrb(&(*b)->head, 'a');
		i--;
	}
	i = cheap->target->index;
	while (i > 1)
	{
		ra(&(*a)->head, 'n');
		i--;
	}
}

void	find_place_in_a(t_stack **a, t_stack **b)
{
	t_node	*tmp;
	int		no_targ;

	no_targ = 0;
	tmp = find_cheapest_in_a(*a, *b);
	if (tmp->value == tmp->target->value)
	{
		find_cheapest_for_no_targ(*a, *b, tmp);
		no_targ = 1;
	}
	if (tmp->index <= (*b)->size / 2 && tmp->target->index <= (*a)->size / 2)
		rotate_both_2(a, b, tmp);
	else if (tmp->index > (*b)->size / 2 && tmp->target->index > (*a)->size / 2)
		rrotate_both_2(a, b, tmp);
	else if (tmp->index <= (*b)->size / 2 && tmp->target->index > (*a)->size / 2)
		rb_rra(a, b, tmp);
	else if (tmp->index > (*b)->size / 2 && tmp->target->index <= (*a)->size / 2)
		rrb_ra(a, b, tmp);
	index_stack(*a);
	index_stack(*b);
	pa(&(*a)->head, &(*b)->head);
	if (no_targ)
		sa(&(*a)->head, 'n');
}

void	push_to_a(t_stack **a, t_stack **b)
{
	while ((*b)->size > 0)
	{
		find_place_in_a(a, b);
		index_stack(*a);
		index_stack(*b);
	}
}

t_node	*get_min_node(t_node *stack)
{
	t_node	*min_node;
	t_node	*tmp;

	tmp = stack;
	min_node = tmp;
	while (tmp)
	{
		if (tmp->value < min_node->value)
			min_node = tmp;
		tmp = tmp->next;
	}
	return (min_node);
}

void	bring_smallest(t_stack **a)
{
	t_node	*tmp;
	int		i;
	
	tmp = get_min_node((*a)->head);
	if (tmp->index <= (*a)->size / 2)
	{
		i = tmp->index;
		while (i > 1)
		{
			ra(&(*a)->head, 'n');
			i--;
		}
	}
	else
	{
		i = (*a)->size - tmp->index + 1;
		while (i > 0)
		{
			rra(&(*a)->head, 'n');
			i--;
		}
	}
}

int	main(int ac, char *av[])
{
	t_stack	*a;
	t_stack	*b;
	// (void)b;
	a = malloc(sizeof(t_stack));
	if (!a)
		return (1);
	b = malloc(sizeof(t_stack));
	if (!b)
		return (1);
	if (ac == 1)
		exit(EXIT_FAILURE);
	if (!valid_args(ac, av, &a))
		exit(EXIT_FAILURE);
	index_stack(a);
	if (stack_sorted(a->head) || a->size <= 3)
	{
		sort_stack3(&a);
		exit(EXIT_SUCCESS);
	}
	push_to_b(&a, &b);
	push_to_a(&a, &b);
	bring_smallest(&a);
	// print_stack1(a, "a");
	index_stack(a);
	index_stack(b);
	exit(EXIT_SUCCESS);
	return (0);
}