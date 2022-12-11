/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 11:14:48 by kpanikka          #+#    #+#             */
/*   Updated: 2021/12/25 19:05:36 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		count;
	char	*str;

	count = 0;
	str = (char *)s;
	while (str[count])
		count++;
	if (c == '\0')
		return (str + count);
	while (count)
	{
		if (str[count] == (char)c)
			return (str + count);
		count--;
	}
	if (str[count] == (char)c)
		return (str + count);
	return (NULL);
}
