/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:55:44 by znichola          #+#    #+#             */
/*   Updated: 2023/01/30 15:40:45 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Parse a command.
	Construct an intermediate command structure.

	We need to check that there is at least 1 item,
	else syntax error.
*/
int	parse_cmd(t_item **cmd, t_token **tok)
{
	t_item	**current;
	int		i;
	int		ret;

	*cmd = NULL;
	current = cmd;
	i = 0;
	ret = parse_item(current, tok);
	while (ret == 0)
	{
		current = &(*current)->next;
		ret = parse_item(current, tok);
		i++;
	}
	if (ret == SYNTAX_ERROR)
	{
		//clear item-list
		return (ret);
	}
	if (i == 0)
	{
		//clear item-list
		return (unexpected_token(*tok));
	}
	return (0);
}
