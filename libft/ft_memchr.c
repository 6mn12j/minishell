/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 21:00:02 by minjupar          #+#    #+#             */
/*   Updated: 2021/05/11 00:11:01 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int target, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (((unsigned char*)s)[i] == (unsigned char)target)
			return ((void*)(s + i));
		i++;
	}
	return (NULL);
}
