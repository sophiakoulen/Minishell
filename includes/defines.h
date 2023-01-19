/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:40:00 by znichola          #+#    #+#             */
/*   Updated: 2023/01/19 08:54:12 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* used in parse_item */
# define NO_MODIFIER -1

/* used in parsing */
# ifdef SUCCESS
#  undef SUCCESS
# endif

# define SUCCESS 0
# define STOP -1
# define SYNTAX_ERROR -2

/* Possible token types corresponding strings defined in structs/t_token.c */
# define NUM_TOKEN_LITERALS 9

# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

enum e_token_type
{
	e_or,			// ||
	e_pipe,			// |
	e_heredoc,		// <<
	e_infile,		// <
	e_append,		// >>
	e_outfile,		// >
	e_open_brace,	// (
	e_close_brace,	// )
	e_and,			// &&
	e_end,			// \n or \r\n
	e_string,
};

# define NUM_BUILTINS 7

enum e_builtin
{
	e_echo,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit,
};

#endif
