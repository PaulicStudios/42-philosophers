/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:03:05 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 18:48:12 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_input_nbr(const char *str, t_info *info)
{
	unsigned int	res;

	res = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			free(info);
			write(2, "Error: invalid argument\n", 25);
			exit(EXIT_FAILURE);
		}
		res = res * 10 + *str - '0';
		str++;
	}
	return (res);
}
