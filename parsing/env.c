/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:51:05 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/25 22:38:49 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_env(char **env)
{
	int		i;
	char	*value;
	char	*temp;
	t_env	*env_lst;

	i = 0;
	while (env[i])
	{
		temp = ft_get_word(env[i], '=');
		value = ft_strdup(env[i] + ft_strlen(temp) + 1);
		env_lst = ft_elstnew(temp, value);
		if (env_lst)
			ft_elstadd_back(&g_msv.env_list, env_lst);
		else
			clean_exit();
		i++;
	}
}

void	unset_env(char *key)
{
	t_env	*env_list;
	// t_env	*env_lst_prev;

	// t_env	*temp;
	env_list = g_msv.env_list;
	// env_lst_prev = NULL;
	while (env_list)
	{
		if (ft_strncmp(key, env_list->next->key, 32767) == 0)
		{
			//temp = env_list ;
			env_list->next = env_list->next->next;
			//	env_lst_prev = env_list->next;
			//free(temp);.
			break ;
		}
		// env_lst_prev = env_list;
		env_list = env_list->next;
	}
}

void	export_env(char *key, char *value)
{
	char	*temp;
	t_env	*env_list;
	t_env	*env_lst;

	env_list = g_msv.env_list;
	if (ft_getenv(key, env_list))
	{
		while (env_list)
		{
			if (ft_strncmp(key, env_list->key, 32767) == 0)
			{
				temp = env_list->value;
				env_list->value = value;
				free(temp);
				break ;
			}
			env_list = env_list->next;
		}
	}
	else
	{
		env_lst = ft_elstnew(key, value);
		if (env_lst)
			ft_elstadd_back(&g_msv.env_list, env_lst);
		else
			clean_exit();
	}
}

/*
*	Accept the string to check in the environment variable and 
	returns the value if key exists
*/
char	*ft_getenv(char *str, t_env *env_list)
{
	//ft_elstprint(g_msv.env_list);
	env_list = g_msv.env_list;
	while (env_list)
	{
		if (ft_strncmp(str, ft_strtrim(env_list->key, " "), 32767) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

int	ft_elstprint(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_elstprint_exp(t_env *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		printf("declare -x %s = \"%s\"\n", lst->key, lst->value);
		lst = lst->next;
		i++;
	}
	return (i);
}