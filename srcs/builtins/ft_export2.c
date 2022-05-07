/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/08 01:57:45 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_value(char *key, char *argv)
{
	int	start;
	int	len;

	start = ft_strlen(key);
	len = ft_strlen(argv);
	if (start + 1 == len)
		return (ft_strdup(""));
	else if (start + 1 > len)
		return (NULL);
	return (ft_substr(argv, start + 1, len));
}
