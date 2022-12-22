/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:02:23 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/22 11:40:42 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*seq_dq(char *temp, char *str, int *j, int *k)
{
	if (str[*j] == '"')
	{
		temp = ft_strjoinchr(temp, '\"');
		(*j)++;
		while (str[*j] && str[*j] != '"')
		{
			if (str[*j] == '$')
			{
				(*j)++;
				while (str[*j] && str[*j] != '"' && str[*j] != ' ' && str[*j] != '$')
				{
					if (!ft_isalnum(str[*j]))
						break ;
					(*k)++;
					(*j)++;
				}
				g_msv.b_temp = ft_get_dword(str + *j - *k);
				g_msv.b_temp = ft_getenv(g_msv.b_temp, g_msv.env_list);
				if (g_msv.b_temp)
					temp = ft_strjoin(temp, g_msv.b_temp);
				(*j)--;
				*k = 0;
			}
			else
			{
				if (str[*j] != '$')
					temp = ft_strjoinchr(temp, str[*j]);
			}
			(*j)++;
		}
	}
	return (temp);
}

char	*trim_seq(char *temp, char *str, int j)
{
	while (str[j])
		temp = ft_strjoinchr(temp, str[j++]);
	if (str[j- 1] == '\'')
		temp = ft_strtrim(temp, "'");
	else if (str[j- 1] == '"')
		temp = ft_strtrim(temp, "\"");
	temp = ft_strtrim(temp, " ");
	return (temp);
}

char	*parse_expand(int i, char *str)
{
	char		*temp;
	int			j;
	int			k;

	temp = "";
	if (g_msv.parse_error)
		return (NULL);
	j = 0;
	k = 0;
	i = 0;
	temp = seq_dq(temp, str, &j, &k);
	if (str[j] == '$')
	{
		j++;
		while (str[j] && str[j] != '"' && str[j] != ' ' && str[j] != '$' )
		{
			k++;
			j++;
		}
		if (k)
		{
			g_msv.b_temp = ft_get_dword_(str + j - k);
			g_msv.b_temp = ft_getenv(g_msv.b_temp, g_msv.env_list);
			if (g_msv.b_temp)
				temp = ft_strjoin(temp, g_msv.b_temp);
		}
		// else
		// 	temp = ft_strjoinchr(temp, '$');
		k = 0;
	}
	temp = trim_seq(temp, str, j);
	return (temp);
}

char	*parse_expand_io(int i, char *str)
{
	char		*temp;
	int			j;
	int			k;

	temp = "";
	if (g_msv.parse_error)
		return (NULL);
	j = 0;
	k = 0;
	i = 0;
	if (str[j] == '>' || str[j] == '<')
	{
		j++;
		if (str[j] == '>' || str[j] == '<')
			temp = ft_strjoinchr(temp, str[j++]);
	}
	while (str[j] && str[j] == ' ')
		j++;
	temp = seq_dq(temp, str, &j, &k);
	if (str[j] == '$')
	{
		j++;
		while (str[j] && str[j] != '"' && str[j] != ' ' && str[j] != '$')
		{
			k++;
			j++;
		}
		g_msv.b_temp = ft_get_dword(str + j - k);
		g_msv.b_temp = ft_getenv(g_msv.b_temp, g_msv.env_list);
		if (g_msv.b_temp)
			temp = ft_strjoin(temp, g_msv.b_temp);
		k = 0;
	}
	temp = trim_seq(temp, str, j);
	return (temp);
}