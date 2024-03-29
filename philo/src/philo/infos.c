/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:08:27 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 19:09:01 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_stop(t_info *info)
{
	bool	stop;

	pthread_mutex_lock(&info->m_stop);
	stop = info->stop;
	pthread_mutex_unlock(&info->m_stop);
	return (stop);
}
