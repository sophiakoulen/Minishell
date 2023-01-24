/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:17:28 by znichola          #+#    #+#             */
/*   Updated: 2023/01/24 13:52:06 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	env_factory(&(t_env){key_str, value_str, next})
	call with blueprint or NULL
	Don't forget to free it after!
 */
t_env	*env_factory(t_env *blueprint)
{
	t_env	*ret;

	ret = (t_env *)x_malloc(sizeof(t_env), 1);
	if (blueprint == NULL)
	{
		ret->key = NULL;
		ret->value = NULL;
		ret->next = NULL;
	}
	else
	{
		ret->key = blueprint->key;
		ret->value = blueprint->value;
		ret->next = blueprint->next;
	}
	return (ret);
}

/*
	Frees a single element of the env
*/
void	env_cleanup(t_env *env)
{
	if (env)
	{
		free(env->key);
		free(env->value);
	}
	free(env);
}

/*
	Frees the whole env linked list
*/
void	env_cleanup_all(t_env *env)
{
	t_env	*previous;

	previous = 0;
	while (env)
	{
		env_cleanup(previous);
		previous = env;
		env = env->next;
	}
	env_cleanup(previous);
}
