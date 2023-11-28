/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:06:05 by ade-tole          #+#    #+#             */
/*   Updated: 2023/11/28 15:25:26 by ade-tole         ###   ########.fr       */
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
			a->target = ft_lstsmallest(b); //missing ft
		else
			a->target = target;
		a = a->next;
	}
}

static	void	comp_price(t_node *a, int size_a, int size_b)
{
	int	r_price;
	int rr_price;

	if (a->index > a->target->index)
		r_price = a->index;
	else
		r_price = a->target->index;
	if ((size_a - a->index) > (size_b - a->target->index))
		rr_price = size_a - a->index;
	else
		rr_price = size_b - a->target->index;
	if (r_price < rr_price)
		a->push_price = r_price;
	else
		a->push_price = rr_price;
}

static	void	set_price(t_node *a, t_node *b)
{
	int	size_a;
	int	size_b;

	size_a = ft_lstsize(a);
	size_b = ft_lstsize(b);
	while (a)
	{
		if (a->upper_half && a->target->upper_half)
		{
			if (a->index > a->target->index)
				a->push_price = a->index;
			else
				a->push_price = a->target->index;
		}
		else if (!a->upper_half && !a->target->upper_half)
		{
			if ((size_a - a->index) > (size_b - a->target->index))
				a->push_price = size_a - a->index;
			else
				a->push_price = size_b - a->target->index;
		}
		else
			comp_price(a, size_a, size_b);
		a = a->next;
	}
}

static	void	move_cheapest(t_node **a, t_node **b)
{
	t_node	*cheapest;
	t_node	*tmp;
	int		size_a;
	int		size_b;
	int		r_price;
	int		rr_price;

	cheapest = *a;
	tmp = *a;
	size_a = ft_lstsize(*a);
	size_b = ft_lstsize(*b);
	while (tmp)
	{
		if (tmp->push_price < cheapest->push_price)
			cheapest = tmp;
		tmp = tmp->next;
	}
	if (cheapest->upper_half && cheapest->target->upper_half)
	{
		if (cheapest->index > cheapest->target->index)
		{
			while (cheapest->target->index)
			{
				rr(a, b);
				cheapest->target->index--;
				cheapest->index--;
			}
			while (cheapest->index)
			{
				ra(a);
				cheapest->index--;
			}
		}
		else
		{
			while (cheapest->index)
			{
				rr(a, b);
				cheapest->index--;
				cheapest->target->index--;
			}
			while (cheapest->target->index)
			{
				rb(b);
				cheapest->target->index--;
			}
		}
	}
	else if (!cheapest->upper_half && !cheapest->target->upper_half)
	{
		if ((size_a - cheapest->index) > (size_b - cheapest->target->index))
		{
			while ((size_b - cheapest->target->index))
			{
				rrr(a, b);
				cheapest->target->index++;
				cheapest->index++;
			}
			while ((size_a - cheapest->index))
			{
				rra(a);
				cheapest->index++;
			}
		}
		else
		{
			while ((size_a - cheapest->index))
			{
				rrr(a, b);
				cheapest->index++;
				cheapest->target->index++;
			}
			while ((size_b - cheapest->target->index))
			{
				rrb(b);
				cheapest->target->index++;
			}
		}
	}
	else
	{
		if (cheapest->index > cheapest->target->index)
			r_price = cheapest->index;
		else
			r_price = cheapest->target->index;
		if ((size_a - cheapest->index) > (size_b - cheapest->target->index))
			rr_price = size_a - cheapest->index;
		else
			rr_price = size_b - cheapest->target->index;
		if (r_price < rr_price)
		{
			if (cheapest->index > cheapest->target->index)
			{
				while (cheapest->target->index)
				{
					rr(a, b);
					cheapest->target->index--;
					cheapest->index--;
				}
				while (cheapest->index)
				{
					ra(a);
					cheapest->index--;
				}
			}
			else
			{
				while (cheapest->index)
				{
					rr(a, b);
					cheapest->index--;
					cheapest->target->index--;
				}
				while (cheapest->target->index)
				{
					rb(b);
					cheapest->target->index--;
				}
			}
		}
		else
		{
			if ((size_a - cheapest->index) > (size_b - cheapest->target->index))
			{
				while ((size_b - cheapest->target->index))
				{
					rrr(a, b);
					cheapest->target->index++;
					cheapest->index++;
				}
				while ((size_a - cheapest->index))
				{
					rra(a);
					cheapest->index++;
				}
			}
			else
			{
				while ((size_a - cheapest->index))
				{
					rrr(a, b);
					cheapest->index++;
					cheapest->target->index++;
				}
				while ((size_b - cheapest->target->index))
				{
					rrb(b);
					cheapest->target->index++;
				}
			}
		}
	}
	pb(a, b);
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
		set_price(*a, *b);
		move_cheapest(a, b);
	}
}
