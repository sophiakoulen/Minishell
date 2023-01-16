/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:30:09 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 14:21:07 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

/* **************************************************************************

	sructs/t_struct.c -- expected structure

	t_struct	*struct_factory(t_struct *blueprint);

	t_struct	*struct_print(t_struct);

	t_struct	*struct_cleanup(t_struct);

   ************************************************************************** */

/*
	basic token linked list
	- the tokenization stage fills this list
	- all subsequent parsing ops happen this list
 */
typedef struct s_token
{
	enum e_token_type	type;
	char				*str;
	struct s_token		*next;
}	t_token;

/*
	tree structure containing the exicution order information
 */
typedef struct s_tree
{
	enum e_token_type	type;
	char				*str;
	struct s_tree		*left;
	struct s_tree		*right;
}	t_tree;

/*
	intermediate structure used to convert tokens list to **args
 */
typedef struct s_word_lst
{
	char				*str;
	struct s_word_lst	*next;
}	t_word_lst;

/*
	info we need during the execution phase.

	- input and output file descriptors we'll need to redirect to
	- full path of the command if it is found in PATH or already a path
	- status of the command. 0 means we can execute.
*/
typedef struct s_cmd_info
{
	int		i_fd;
	int		o_fd;
	char	*full_path;
	int		status;
}	t_cmd_info;

/*
	file descriptors we need during execution phase.

	- pipes : pipes to redirect a cmd's output into another cmd's input
	- hd_pipes : pipes to execute heredocs
	- infile_fds : file descriptors corresponding to input files
	- outfile_fds : file descriptors corresponding to output files.
*/
typedef struct s_fds
{
	int	**pipes;
	int	**hd_pipes;
	int	*infile_fds;
	int	*outfile_fds;
}	t_fds;

/*
	t_cmd is the basic command structure that contains the information needed
	by the pipeline execution stage.

	The parsing / input-processing stage needs to extract this information,
	in the form of a t_cmd array or linked list.

	cmd.args is the argument array, the first being the name of the command, the rest
	being the arguments, as we need to pass to the execve function.

	cmd.in is info about the input redirection:
		The input redirection is the last item from a cmd in the form
		`< WORD` or `<< WORD`.
		in.str is the corresponding WORD.
		in.type to know whether input from file or heredoc

	cmd.out is info about the output redirection:
		The output redirection is the last item in the form
		`> WORD` or `>> WORD`.
		out.str is the WORD.
		out.type to know whether append mode or not.
*/

typedef	struct s_redir
{
	int		type; //change this to enum later to avoid mistakes
	char	*str;
}	t_redir;

typedef struct s_cmd
{
	char	**args;
	t_redir	*in;
	t_redir	*out;
}	t_cmd;

/**
 * Screen posiiton struct.
 * used in print tree and TODO: for cool intro animations
 */
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

#endif
