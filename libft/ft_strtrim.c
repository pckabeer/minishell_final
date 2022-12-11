/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:05:16 by kpanikka          #+#    #+#             */
/*   Updated: 2022/01/02 10:43:44 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s1_len;
	char	*str;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (0);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	s1_len = ft_strlen(s1 + i);
	while (s1_len > 0 && (ft_strchr(set, *(s1 + i + s1_len - 1))))
		s1_len--;
	str = (char *)ft_substr(s1, i, s1_len);
	return (str);
}
