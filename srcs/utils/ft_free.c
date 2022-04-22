/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:05:23 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/22 22:16:47 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_two_ptr(char **ptr)
{
	char	**cur;

	cur = ptr;
	while (*cur != NULL)
		free(*(cur++));
	free(ptr);
}
