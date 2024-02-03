/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 05:50:12 by alaassir          #+#    #+#             */
/*   Updated: 2024/02/03 13:01:14 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_sig(int sig, int pid)
{
	int	n;

	n = kill(pid, sig);
	if (n == -1)
	{
		ft_putstr(RED"pid is not a valid pid\n"RESET);
		exit(EXIT_FAILURE);
	}
}

static void	send_char(char c, int pid)
{
	int	bits;

	bits = 7;
	while (bits >= 0)
	{
		if (((c >> bits) & 1) == 1)
			send_sig(SIGUSR1, pid);
		else
			send_sig(SIGUSR2, pid);
		bits--;
		usleep(800);
	}
}

static void	send_message(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(str[i], pid);
		i++;
	}
}

static int	parse_input(char *str)
{
	int	n;

	n = ft_atoi(str);
	if (n <= 1)
	{
		ft_putstr(RED"Invalid PID\n"RESET);
		exit(EXIT_FAILURE);
	}
	return (n);
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
	{
		ft_putstr("Usage: './client PID_SERVER STRING_TO_PASS'\n");
		return (-1);
	}
	pid = parse_input(av[1]);
	send_message(av[2], pid);
	send_message("\n", pid);
	return (0);
}
