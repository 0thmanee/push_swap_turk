/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:55:25 by obouchta          #+#    #+#             */
/*   Updated: 2024/01/24 16:33:52 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	valid_nbr(char *nbr)
{
	int	i;

	i = 0;
	if (ft_strlen(nbr) == 1 && (nbr[0] == '-' || nbr[0] == '+'))
		return (0);
	if (nbr[i] == '-' || nbr[i] == '+')
		i++;
	if (!nbr[i])
		return (0);
	while(nbr[i])
	{
		if (nbr[i] < '0' || nbr[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	not_int(char *nbr)
{
	if (ft_strlen(nbr) >= 19)
		return (1);
	if (ft_atoi(nbr) < -2147483648 || ft_atoi(nbr) > 2147483647)
		return (1);
	return (0);
}

int	check_duplicated(t_stack *stack, int data)
{
	t_node	*tmp;

	if (!stack || !stack->head)
		return (0);
	tmp = stack->head;
	while (tmp)
	{
		if (tmp->value == data)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int add_to_stack(t_stack **stack, int data, int index)
{
	t_node	*node;
	t_node	*tmp;
	
	if (check_duplicated(*stack, data))
		return (0);
	node = malloc(sizeof(t_node));
	if (!node)
		return (0);
	node->value = data;
	node->index = index;
	node->next = NULL;
	if (!(*stack)->head)
	{
		(*stack)->head = node;
		(*stack)->size = 1;
		return (1);
	}
	tmp = (*stack)->head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	(*stack)->size++;
	return (1);
}

void	free_lomor(char **strings)
{
	int		i;

	if (!strings)
		return ;
	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

int	valid_args(int ac, char *av[], t_stack **a)
{
	int		i;
	int		j;
	int		k;
	char	**strings;
	
	i = 0;
	k = 0;
	while (++i < ac)
	{
		strings = ft_split(av[i], ' ');
		if (strings)
		{
			j = -1;
			while (strings[++j])
			{
				if (!strings[j] || !valid_nbr(strings[j]) || not_int(strings[j]))
					(printf("Error\n"), free_lomor(strings), exit(EXIT_FAILURE));
				if (!add_to_stack(a, ft_atoi(strings[j]), ++k))
					(printf("Error\n"), free_lomor(strings), exit(EXIT_FAILURE));
			}
		}
		else
			(printf("Error\n"), free_lomor(strings), exit(EXIT_FAILURE));
	}
	free_lomor(strings);
	return (1);
}

void	index_stack(t_stack *stack)
{
	t_node	*tmp;
	int		i;

	if (!stack)
		return ;
	tmp = stack->head;
	if (!tmp)
	{
		stack->size = 0;
		return ;
	}
	i = 1;
	while (tmp)
	{
		tmp->index = i;
		stack->size = i;
		i++;
		tmp = tmp->next;
	}
}