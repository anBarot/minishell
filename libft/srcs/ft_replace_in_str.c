/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_in_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:50:53 by abarot            #+#    #+#             */
/*   Updated: 2020/07/29 00:23:24 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace_in_str(char *old_str, char *to_replace, char *elt)
{
	char	*n_str;
	int		i_nstr;
	int		elt_size;

	i_nstr = 0;
	if (!old_str || !elt || !(n_str = ft_calloc(ft_strlen(old_str) + 
		(ft_count(old_str, elt) * ft_strlen(elt)), 1)))
		return (0);
	while (*old_str)
	{
		elt_size = ft_strlen(elt);
		while (*old_str && ft_strncmp(old_str, to_replace, ft_strlen(to_replace)))
		{
			n_str[i_nstr] = *old_str;
			old_str++;
			i_nstr++;
		}
		if (*old_str)
		{
			while (elt_size)
			{
				n_str[i_nstr] = elt[ft_strlen(elt) - elt_size];
				elt_size--;
				i_nstr++;
			}
			old_str = old_str + ft_strlen(to_replace);
		}
	}
	return (n_str);
}
