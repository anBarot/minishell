/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:14:54 by abarot            #+#    #+#             */
/*   Updated: 2020/09/29 17:50:13 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest || !src)
		return (0);
	while (n)
	{
		*(char *)dest = *(const char *)src;
		dest++;
		src++;
		n--;
	}
	return (dest);
}
