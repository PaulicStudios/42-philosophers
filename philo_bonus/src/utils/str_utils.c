/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:25:27 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/31 17:25:51 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_philo_sem_meals_name(unsigned int id)
{
	char	*sem_name;
	char	*str_id;

	str_id = ft_itoa(id);
	sem_name = ft_strjoin("sem_philo_", str_id);
	free(str_id);
	return (sem_name);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	if (dstsize == 0)
		return (len_src);
	i = 0;
	while (i < dstsize - 1 && i < len_src)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (len_src);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	i = 0;
	while (i < dstsize - len_dst - 1 && i < len_src)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = 0;
	return (len_dst + len_src);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*dst;

	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!dst)
		return (0);
	ft_strlcpy(dst, s1, len_s1 + 1);
	ft_strlcat(dst, s2, len_s1 + len_s2 + 1);
	return (dst);
}
