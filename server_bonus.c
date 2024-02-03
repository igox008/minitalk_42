/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 05:54:43 by alaassir          #+#    #+#             */
/*   Updated: 2024/02/03 13:07:40 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	how_much(int c)
{
	if (c == 12)
		return (2);
	else if (c == 14)
		return (3);
	else if (c == 15)
		return (4);
	return (1);
}

static int	handle_out(char c, int flush)
{
	static char	prnt[5];
	static int	bits;
	static int	i;

	if (flush == TRUE)
	{
		(1) && (bits = 0, i = 0);
		ft_bzero(prnt);
	}
	else
	{
		if (!bits)
		{
			ft_putstr(prnt);
			ft_bzero(prnt);
			bits = how_much(c >> 4);
			i = 0;
		}
		prnt[i] = c;
		i++;
		bits--;
	}
	return (1);
}

static void	sig_hand(int sig, siginfo_t *info, void *context)
{
	static int			bits;
	static unsigned int	final_char;
	static int			pid;

	(void)context;
	if ((!pid || pid != info->si_pid) && handle_out('\0', TRUE))
		(1) && (pid = info->si_pid, bits = 0, final_char = 0);
	if (sig == SIGUSR1)
		final_char = ((final_char << 1) | 1);
	else if (sig == SIGUSR2)
		final_char = (final_char << 1);
	bits++;
	if (bits > 7)
	{
		if ((final_char == '\n' && handle_out('\n', FALSE))
			|| final_char == '\0')
		{
			if (final_char == '\n' && kill(pid, SIGUSR2) == -1)
				(1) && (bits = 0, final_char = 0);
			handle_out('\0', TRUE);
		}
		else
			handle_out(final_char, FALSE);
		(1) && (final_char = 0, bits = 0);
	}
}

int	main(void)
{
	static int			pid;
	struct sigaction	sig_act;

	if (!pid)
		pid = getpid();
	ft_putstr("Server PID: ");
	ft_putnbr(pid);
	ft_putstr("\n");
	sig_act.sa_sigaction = sig_hand;
	sig_act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig_act, NULL) == -1
		|| sigaction(SIGUSR2, &sig_act, NULL) == -1)
		ft_putstr(RED"sigaction fail"RESET);
	while (1)
		pause();
	return (0);
}
