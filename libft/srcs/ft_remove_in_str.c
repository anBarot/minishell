/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_in_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:38:02 by abarot            #+#    #+#             */
/*   Updated: 2020/04/21 17:03:42 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_check_in_charset(char c, char *char_set)
{
	while (*char_set)
	{
		if (c == *char_set)
			return (1);
		else
			char_set++;
	}
	return (0);
}

char	*ft_remove_in_str(char *str, char *char_set)
{
	int		in_str;
	char	*n_str;

	in_str = 0;
	if (!(n_str = calloc(sizeof(char), strlen(str))) || !str || !char_set)
		return (0);
	while (*str)
	{
		if (ft_strchr(char_set, *str))
			str++;
		else
		{
			n_str[in_str] = *str;
			in_str++;
			str++;
		}
	}
	return (n_str);
}
