/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:55:46 by abarot            #+#    #+#             */
/*   Updated: 2020/07/28 18:01:34 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count(char *str, char *elt)
{
	int count;

	count = 0;
	if (!str || !elt)
		return (0);
	while (*str)
	{
		if (!ft_strncmp(str, elt, ft_strlen(elt)))
			count++;
		str++;
	}
	return (count);
}
