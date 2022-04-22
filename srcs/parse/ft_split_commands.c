/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/20 19:27:43 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_quote(char c)
{
	static char	flag = 0;

	if (c == '\'' || c == '"')
	{
		if (flag == 0)
		{
			flag = c;
			return (1);
		}
		if (c == '\'' && flag == '\'')
		{
			flag = 0;
			return (1);
		}
		else if (c == '"' && flag == '"')
		{
			flag = 0 ;
			return (1);
		}
	}
	return (c == flag);
}

int	get_word_count(char *str)
{
	int		i;
	int		flag;
	int		word_count;

	flag = 0;
	i = -1;
	word_count = 0;
	while (str[++i])
	{
		if (change_quote(str[i]))
			flag = !flag;
		if (flag == 0 && str[i + 1] == '\0')
			word_count++;
		else if (flag == 0 && str[i] != ' ' && str[i + 1] == ' ')
		{
			word_count++;
			i++;
		}
	}
	return (word_count);
}

int	get_word_len(int start, char*str)
{
	int	flag;
	int	len;

	flag = 0;
	len = 0;
	while (str[start + len])
	{
		if (change_quote(str[start + len]))
			flag = !flag;
		if (flag == 0 && str[start + len] == ' ')
			return (len);
		len++;
	}
	return (len);
}

int	get_start(int start, char *str)
{
	int	flag;

	while (str[start] && (str[start] == ' '))
	{
		if (change_quote(flag))
			flag = !flag;
		start ++;
	}
	return (start);
}

char	**ft_split_commands(char *str)
{
	//1. 단어 갯수를 센다
	//2. 단어 갯수만큼 말록 한다.
	int		i;
	int		word_len;
	int		start;
	int		word_cnt;
	char	**command_array;

	word_cnt = get_word_count(str);
	command_array = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!command_array)
		ft_error();
	i = -1;
	start = get_start(0, str);
	while (++i < word_cnt)
	{
		word_len = get_word_len(start, str);
		command_array[i] = (char *)malloc(sizeof(char) * (word_len +1));
		if (!command_array[i])
			ft_error();
		ft_strlcpy(command_array[i], str + start, word_len + 1);
		start = get_start(start + word_len, str);
	}
	command_array[i] = (char *) '\0';
	return (command_array);
}
