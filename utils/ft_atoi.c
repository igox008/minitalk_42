/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:06:44 by alaassir          #+#    #+#             */
/*   Updated: 2024/02/03 04:02:36 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	ft_atoi(char *str)
{
	int		i;
	int		s;
	long	rsl;

	(1) && (i = 0, s = 1, rsl = 0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (((rsl * 10) + (str[i] - 48) * s > 2147483647
				|| (rsl * 10) + (str[i] - 48) * s < -2147483648)
			&& ft_putstr(RED"INT overflow detected\n"RESET))
			exit(1);
		rsl = (rsl * 10) + (str[i] - 48);
		i++;
	}
	return ((int)(rsl * s));
}
