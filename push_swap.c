/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:06:05 by ade-tole          #+#    #+#             */
/*   Updated: 2023/11/26 23:29:08 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	set_index(t_node *stack)
{
	int	i;
	int	stack_half;

	stack_half = ft_lstsize(stack) / 2;
	i = 0;
	while (stack)
	{
		stack->index = i;
		if (i <= stack_half)
			stack->upper_half = true;
		else
			stack->upper_half = false;
		i++;
		stack = stack->next;
	}
}

static	void	set_target(t_node *a, t_node *b)
{
	t_node	*tmp;
	t_node	*target;
	int		target_value;

	while (a)
	{
		target_value = INT_MAX;
		tmp = b;
		while (tmp)
		{
			if (a->data < tmp->data && tmp->data < target_value)
			{
				target_value = tmp->data;
				target = tmp;
			}
			tmp = tmp->next;
		}
		if (target_value == INT_MAX)
			b->target = ft_lstsmallest(b); //missing ft
		else
			b->target = target;
		b = b->next;
	}
}

void	push_swap(t_node **a, t_node **b)
{
	pb(a, b);
	pb(a, b);

	while (*a)
	{
		set_index(*a);
		set_index(*b);
		set_target(*a, *b);
	}
}
