/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:06:03 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 19:06:22 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_stop(t_info *info)
{
	pthread_mutex_lock(&info->m_stop);
	info->stop = true;
	pthread_mutex_unlock(&info->m_stop);
}
