/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:51:45 by kpanikka          #+#    #+#             */
/*   Updated: 2021/12/30 16:15:47 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*a;
	char	*b;

	i = 0;
	if (!dst && !src)
		return (NULL);
	a = (char *) dst;
	b = (char *) src;
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return ((void *) a);
}
