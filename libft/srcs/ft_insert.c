/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:37:01 by abarot            #+#    #+#             */
/*   Updated: 2020/10/01 10:17:07 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_insert(char *str, char *elt, unsigned int index)
{
	char	*res;

	if (!str || !elt || index > ft_strlen(str) ||
		!(res = (char *)ft_calloc(1, ft_strlen(str) + ft_strlen(elt) + 1)))
		return (0);
	memcpy(res, str, index);
	memcpy(res + index, elt, ft_strlen(elt));
	memcpy(res + index + ft_strlen(elt), str + index, ft_strlen(str) - index);
	return (res);
}
