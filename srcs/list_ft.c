/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:08:29 by abarot            #+#    #+#             */
/*   Updated: 2020/07/27 18:41:36 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_list_size(t_list *list)
{
	int i;

	if (!list)
		return (0);
	i = 1;
	while (list->next)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	ft_clear_list(t_list **list)
{
	t_list	*tmp;

	while ((*list)->next)
	{
		tmp = *list;
		free((*list)->data);
		*list = (*list)->next;
		free(tmp);
	}
	free((*list)->data);
	free(*list);
}

int		ft_append_elt(t_list **list, char *elt)
{
	t_list *new_elt;
	t_list	*head;

	head = *list;
	if (!list || !elt || !(new_elt = malloc(sizeof(t_list))))
		return (EXIT_FAILURE);
	new_elt->data = elt;
	new_elt->next = 0;
	if (!(*list))
	{
		(*list) = new_elt;
		return (EXIT_SUCCESS);
	}
	while (head->next)
		head = head->next;
	head->next = new_elt;
	return (EXIT_SUCCESS);
}