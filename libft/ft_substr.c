/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 11:36:38 by kpanikka          #+#    #+#             */
/*   Updated: 2021/12/31 20:49:36 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (0);
	if (len > (size_t)ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	substr = ft_calloc(len + 1, 1);
	if (substr)
		return (ft_memcpy(substr, s + start, len));
	return (NULL);
}
