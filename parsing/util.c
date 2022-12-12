/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:29:56 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/10 20:08:16 by kpanikka         ###   ########.fr       */
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