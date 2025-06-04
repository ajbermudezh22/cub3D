/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:01:34 by fvargas           #+#    #+#             */
/*   Updated: 2025/03/16 12:56:07 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
	It returns the pointer to the last occurence of c, or NULL
 */
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	s += i;
	while (i > 0 && *s != (char)c)
	{
		s--;
		i--;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
