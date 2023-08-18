/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchoy-me <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:33:51 by jchoy-me          #+#    #+#             */
/*   Updated: 2023/08/18 16:16:51 by jchoy-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *) &(s[i]));
		i++;
	}
	if (s[i] == (char) c)
		return ((char *) &(s[i]));
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		nbytes;

	nbytes = ft_strlen(s1) + 1;
	ptr = (char *) malloc(sizeof(char) * nbytes);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, nbytes);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	nbytes;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	nbytes = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = (char *) malloc(sizeof(char) * nbytes);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, ft_strlen(s1) + 1);
	ft_strlcat(dest, s2, nbytes);
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && (i < dstsize))
		i++;
	while ((i + j + 1) < dstsize && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sbstr;
	size_t	i;
	size_t	strsize;

	i = 0;
	if (s == NULL)
		return (NULL);
	strsize = ft_strlen(s);
	if (len > strsize - start)
		len = strsize - start;
	if (start > strsize)
		len = 0;
	sbstr = (char *) malloc(sizeof(char) * (len + 1));
	if (sbstr == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0' && start < strsize)
	{
		sbstr[i] = s[start + i];
		i++;
	}
	sbstr[i] = '\0';
	return (sbstr);
}