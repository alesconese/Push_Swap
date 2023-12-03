/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:09:27 by ade-tole          #+#    #+#             */
/*   Updated: 2023/12/02 20:12:53 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	rotate_stacks(t_node **a, t_node **b, t_node *cheapest)
{
	if (cheapest->index > cheapest->target->index)
	{
		while (cheapest->target->index)
		{
			rr(a, b);
			cheapest->target->index--;
			cheapest->index--;
		}
		while (cheapest->index--)
			rb(b);
	}
	else
	{
		while (cheapest->index)
		{
			rr(a, b);
			cheapest->index--;
			cheapest->target->index--;
		}
		while (cheapest->target->index--)
			ra(a);
	}
}

static	void	rev_rotate_stacks(t_node **a, t_node **b, t_node *cheapest)
{
	int	size_a;
	int	size_b;

	size_a = ft_lstsize(*a);
	size_b = ft_lstsize(*b);
	if ((size_b - cheapest->index) > (size_a - cheapest->target->index))
	{
		while ((size_a - cheapest->target->index++))
		{
			rrr(a, b);
			cheapest->index++;
		}
		while ((size_b - cheapest->index++))
			rrb(b);
	}
	else
	{
		while ((size_b - cheapest->index) && cheapest->index++)//para el caso size 1 index 0  hay que incrementar al final para que no entre en el bucle
		{
			rrr(a, b);
			cheapest->target->index++;
		}
		while ((size_a - cheapest->target->index++))
			rra(a);
	}
}

static	void	find_best_rotation(t_node **a, t_node **b, t_node *cheapest)
{
	int	size_a;
	int	size_b;
	int	r_price;
	int	rr_price;

	size_a = ft_lstsize(*a);
	size_b = ft_lstsize(*b);
	if (cheapest->index > cheapest->target->index)
		r_price = cheapest->index;
	else
		r_price = cheapest->target->index;
	if ((size_b - cheapest->index) > (size_a - cheapest->target->index))
		rr_price = size_b - cheapest->index;
	else
		rr_price = size_a - cheapest->target->index;
	if (r_price < rr_price)
		rotate_stacks(a, b, cheapest);
	else
		rev_rotate_stacks(a, b, cheapest);
}

void	move_cheapest(t_node **a, t_node **b)
{
	t_node	*cheapest;
	t_node	*tmp;

	cheapest = *b;
	tmp = *b;
	while (tmp)
	{
		if (tmp->push_price < cheapest->push_price)
			cheapest = tmp;
		tmp = tmp->next;
	}
	if (cheapest->upper_half && cheapest->target->upper_half)
		rotate_stacks(a, b, cheapest);
	else if (!cheapest->upper_half && !cheapest->target->upper_half)
		rev_rotate_stacks(a, b, cheapest);
	else
		find_best_rotation(a, b, cheapest);
	pa(a, b);
}

void	sort_3(t_node **a)
{
	if ((*a)->data > (*a)->next->data) // 2 1 3 | 3 1 2 | 3 2 1
	{
		if ((*a)->data > (*a)->next->next->data) // 3 1 2 | 3 2 1
			ra(a); // 3 1 2 >> 1 2 3 | 3 2 1 >> 2 1 3
		if ((*a)->data > (*a)->next->data) // 2 1 3
			sa(a); // 2 1 3 >> 1 2 3
	}
	else if ((*a)->next->data > (*a)->next->next->data) // 1 3 2 | 2 3 1
	{
		rra(a); // 2 3 1 >> 1 2 3 | 1 3 2 >> 2 1 3
		if ((*a)->data > (*a)->next->data) // 2 1 3
			sa(a); // 2 1 3 >> 1 2 3
	}
}
