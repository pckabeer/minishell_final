/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabeer <skabeer@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:02:30 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/15 09:39:22 by skabeer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (!dstsize)
		return (src_len);
	while (i < (dstsize - 1))
	{
		if (!src[i])
		{
			dst[i] = '\0';
			break ;
		}
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
