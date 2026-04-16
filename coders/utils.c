/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:41:37 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 20:06:10 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	dup = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] != 0)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

int	is_str_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != 0)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long int	ft_atol(char *nbr)
{
	int			i;
	long int	value;

	i = 0;
	value = 0;
	while (nbr[i] != 0)
	{
		value = value * 10 + (nbr[i] - '0');
		i++;
	}
	return (value);
}

long int	get_time(long int start_time)
{
	struct timeval	tv;
	long int		end_time;

	gettimeofday(&tv, NULL);
	if (start_time == -1)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	end_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (end_time - start_time);
}
