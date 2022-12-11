/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 10:51:43 by kpanikka          #+#    #+#             */
/*   Updated: 2022/01/02 11:10:12 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	s_len;
	char			*str;

	if (!s)
		return (0);
	i = -1;
	s_len = ft_strlen(s);
	str = (char *)ft_strdup(s);
	while (str && ++i < s_len)
		str[i] = f(i, str[i]);
	return (str);
}
