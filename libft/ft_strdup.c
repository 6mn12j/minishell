/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:43:45 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/18 15:42:34 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*temp;
	size_t		i;

	i = 0;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!temp)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		temp[i] = ((char *)s1)[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}
