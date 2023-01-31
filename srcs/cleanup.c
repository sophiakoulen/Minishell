/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:25:17 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/31 10:53:59 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	item_list_cleanup(t_item *lst);

void	pipeline_cleanup(t_list *pipeline)
{
	ft_lstclear(&pipeline, (void (*)(void *))item_list_cleanup);
}

static void	item_list_cleanup(t_item *lst)
{
	t_item	*previous;

	previous = 0;
	while (lst)
	{
		if (previous)
			free(previous->word);
		free(previous);
		previous = lst;
		lst = lst->next;
	}
	if (previous)
		free(previous->word);
	free(previous);
}
