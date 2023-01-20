/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:32:11 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/20 13:32:44 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_item	*copy_item_deep(t_item *item);

t_pipeline	*expand_pipeline(t_parsed_pipeline *intermediate, t_env *env)
{
	t_pipeline	*p;
	int			i;

	p = x_malloc(sizeof(*p), 1);
	p->n_cmds = intermediate->n_cmds;
	p->cmds = x_malloc(sizeof(*(p->cmds)), p->n_cmds);
	i = 0;
	while (i < p->n_cmds)
	{
		expand_cmd(&p->cmds[i], intermediate->cmds[i], env);
		i++;
	}
	return (p);
}

/*
	Currently doesn't do any expansion,
	just translate from one form into the other.

	added in quotes removal with the quote_removal before
	the dupe
*/
void	expand_cmd(t_cmd *definitive, t_parsed_cmd *intermediate, t_env *env)
{
	t_list	*current;
	int		i;
	int		len;

	(void)env;

	/* copy the argument list into array */
	len = ft_lstsize(intermediate->args);
	definitive->args = x_malloc(sizeof(char *), len + 1);
	// definitive->args = x_malloc(sizeof(*(definitive->args)), len + 1);
	i = 0;
	current = intermediate->args;
	while (i < len)
	{
		definitive->args[i] = ft_strdup(quote_removal(current->content)); //TO DO: MALLOC PROTECTION
		current = current->next;
		i++;
	}
	definitive->args[i] = 0;

	/* copy the redirections list */
	definitive->redirs = ft_lstmap(intermediate->redirs, (void *(*)(void *))copy_item_deep, (void (*)(void *))item_cleanup_deep);
}

static t_item	*copy_item_deep(t_item *item)
{
	t_item	*new_item;

	new_item = x_malloc(sizeof(*new_item), 1);
	new_item->modifier = item->modifier;
	new_item->word = ft_strdup(item->word);
	return (new_item);
}
