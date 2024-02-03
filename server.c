/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 05:54:43 by alaassir          #+#    #+#             */
/*   Updated: 2024/02/03 13:07:56 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sig_hand(int sig, siginfo_t *info, void *context)
{
	static int				bits;
	static unsigned char	final_char;
	static int				pid;

	(void)context;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		bits = 0;
		final_char = 0;
	}
	if (sig == SIGUSR1)
		final_char = ((final_char << 1) | 1);
	else if (sig == SIGUSR2)
		final_char = (final_char << 1);
	bits++;
	if (bits > 7)
	{
		write(1, &final_char, 1);
		final_char = 0;
		bits = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sig_act;

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
