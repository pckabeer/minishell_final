/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:02:23 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/24 21:29:58 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*seq_dq(char *temp, char *str, int *j, int *k)
{
	if (str[*j] == '"')
	{
		//temp = ft_strjoinchr(temp, '\"');
		(*j)++;
		while (str[*j] && str[*j] != '"')
		{
			if (str[*j] == '$'  && str[*j+1] != ' ' && str[*j+1] != '"')
			{
				(*j)++;
				if (str[*j] == '?')
				{
					printf("error: %d not allowed in double quotes\n",g_msv.exit_status);
					temp = ft_strjoin(temp, ft_itoa(g_msv.exit_status));
					(*j)++;
				}
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
			else if (str[*j] == '$' && (str[*j+1] == ' ' ||  str[*j+1] == '"'))
				temp = ft_strjoinchr(temp, '$');
			else
			{
				if (str[*j] != '$')
					temp = ft_strjoinchr(temp, str[*j]);
			}
			(*j)++;
		}
	(*j)++;
	}
	return (temp);
}

char	*trim_seq(char *temp, char *str, int j)
{
	temp = ft_strtrim(temp, " ");
	if (str[j- 1] == '\'')
		temp = ft_strtrim(temp, "'");
	else if (str[j- 1] == '"')
		temp = ft_strtrim(temp, "\"");
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
	// if(str[0] == '$' && !str[1])
	// 	return ("$");
	while (str[j] && str[j] != '"' && str[j] != '$' && str[j] != '\'' && str[j] != ' ')
	{
		if (str[j] != '\'')
		temp = ft_strjoinchr(temp, str[j]);
		j++;
	}
	if (str[j] == '\'')
	{
		j++;
		while (str[j] && str[j] != '\'')
		{
			temp = ft_strjoinchr(temp, str[j]);
			j++;
		}
		j++;
	}
	temp = seq_dq(temp, str, &j, &k);
	if (str[j] == '$' && str[j+1] != ' ')
	{
		if (str[++j] == '?')
		{
			temp = ft_strjoin(temp, ft_itoa(g_msv.exit_status));
			j++;
		}
		else if ( str[j] == '\'' || str[j] == '"' || str[j] == ' ')
			temp = ft_strjoinchr(temp, '$');

		while (str[j] && str[j] != '"' && str[j] != ' ' && str[j] != '$' )
		{
			k++;
			j++;
		}
		if (k)
		{
			g_msv.b_temp = ft_get_dword_(str + j - k);
						// printf("--> string : %s\n", g_msv.b_temp );

			g_msv.b_temp = ft_getenv(g_msv.b_temp, g_msv.env_list);
			if (g_msv.b_temp)
				temp = ft_strjoin(temp, g_msv.b_temp);
		}
		else if (str[j] == '$' && str[j+1] == ' ')
			temp = ft_strjoinchr(temp, '$');
		else if (str[j] == '$' && !str[j+1])
				temp = ft_strjoinchr(temp, '$');
		k = 0;
	}
	//temp = trim_seq(temp, str, j);
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
			temp = ft_strjoinchr(temp, str[j++]);
		if (str[j] == '>' || str[j] == '<')
			temp = ft_strjoinchr(temp, str[j++]);
	}
	// printf("--> string : %s\n", temp);
	while (str[j] && str[j] == ' ')
		j++;
	temp = seq_dq(temp, str, &j, &k);
	if (str[j] == '$')
	{
		j++;
		if (str[j] == '?')
		{
			temp = ft_strjoin(temp, ft_itoa(g_msv.exit_status));
			j++;
		}
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
	
	while (str[j])
		temp = ft_strjoinchr(temp, str[j++]);
	// temp = trim_seq(temp, str, j);
	return (temp);
}