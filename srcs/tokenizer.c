/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:42:40 by znichola          #+#    #+#             */
/*   Updated: 2023/01/12 00:10:38 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Returns the corresponding string for the token type,
 * or NULL if not in list.
*/
const char	*ret_token_literal(enum e_token_type n)
{
	static const char	*tok_strings[NUM_TOKEN_LITERALS] = {
		"||",
		"|",
		"<<",
		"<",
		">>",
		">",
		"(",
		")",
		"&&",
	};

	if (n > NUM_TOKEN_LITERALS || n < 0)
		return (NULL);
	return (tok_strings[n]);
}

int	check_token_literals(char *str)
{
	int	i;

	i = -1;
	if (*str == '\0' || *str == '\n' || (*str == '\r' && *str + 1 == '\n'))
		return (e_end);
	while (++i < NUM_TOKEN_LITERALS)
	{
		if (!ft_strncmp(str,
				ret_token_literal(i),
				ft_strlen(ret_token_literal(i))))
			return (i);
	}
	return (-1);
}

/**
 * TODO: this needs to be fixed!
 * The ' " are ignored and we still parce the tokens contained within
*/
static t_token	*lexer(char	**str)
{
	t_token	*tok;
	int		i;

	tok = allocate(sizeof(t_token), 1);
	tok->next = NULL;
	tok->type = check_token_literals(*str);
	if (tok->type == e_end)
		;
	else if ((int)tok->type != -1)
		*str = *str + ft_strlen(ret_token_literal(tok->type));
	else
	{
		i = -1;
		while ((*str)[i++] && (int)tok->type == -1)
			tok->type = check_token_literals(*str + i);
		if ((int)tok->type != -1)
			i--;
		tok->type = e_string;
		tok->str = ft_substr(*str, 0, i);
		*str += i;
	}
	return (tok);
}

/**
 * This will make a new linked list of the found tokens.
 */
t_token	*construct_tok_list(char *str)
{
	t_token	*start;
	t_token	*end;
	t_token	*tmp;

	start = NULL;
	while (1)
	{
		tmp = lexer(&str);
		// ft_printf("lexer type %s		", ret_token_literal(tmp->type));
		// ft_printf("lexer str\"%s\"\n", tmp->str);
		if (start == NULL)
		{
			start = tmp;
			end = start;
		}
		else
		{
			end->next = tmp;
			end = end->next;
		}
		if (tmp->type == e_end)
			return (start);
	}
}
