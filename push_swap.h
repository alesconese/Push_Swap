/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:31:20 by ade-tole          #+#    #+#             */
/*   Updated: 2023/12/02 19:54:46 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_node
{
	int				data;
	int				index;
	bool			upper_half;
	int				push_price;
	struct s_node	*target;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

t_node	*init_stack(t_node **stack, char **argv);

void	push_swap(t_node **a, t_node **b);

void	sort_3(t_node **a);

void	move_cheapest(t_node **a, t_node **b);

t_node	*ft_lstlast(t_node *head);

int		ft_lstsize(t_node *stack);

t_node	*ft_lstsmallest(t_node *stack);

int		ft_lstsorted(t_node *a);

void	free_stack(t_node **stack);

void	free_error(t_node **a);

void	sa(t_node **a);

void	sb(t_node **b);

void	ss(t_node **a, t_node **b);

void	pa(t_node **a, t_node **b);

void	pb(t_node **a, t_node **b);

void	ra(t_node **a);

void	rb(t_node **b);

void	rr(t_node **a, t_node **b);

void	rra(t_node **a);

void	rrb(t_node **b);

void	rrr(t_node **a, t_node **b);

#endif
