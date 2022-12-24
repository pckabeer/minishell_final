/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:29:56 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/24 03:20:32 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_word(char *str, char ch)
{
	int	i;

	i = ft_strchr(str, ch) - str;
	return (ft_substr(str, 0, i));
}

char	*ft_get_dword(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

char	*ft_get_dword_(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i])|| str[i] == '_')
		i++;
	return (ft_substr(str, 0, i));
}

char	*ft_strjoinchr(char *str, char ch)
{
	char	*temp_two;

	temp_two = ft_calloc(2, 1);
	temp_two[0] = ch;
	temp_two[1] = '\0';
	g_msv.temp = ft_strjoin(str, temp_two);
	free(temp_two);
	return (g_msv.temp);
}


