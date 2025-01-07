/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:04:37 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/07 08:22:23 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive_char_signal(int sig, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		bit_count = 0;
	static pid_t	client_pid = 0;

	(void) context;
	if (info->si_pid)
		client_pid = info->si_pid;
	if (sig == SIGUSR1)
		c &= ~(1 << bit_count);
	else if (sig == SIGUSR2)
		c |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		ft_putchar_fd(c, 1);
		if (c == '\0')
			ft_putchar_fd('\n', 1);
		c = 0;
		bit_count = 0;
	}
	kill(client_pid, sig);
}

int	main(void)
{
	pid_t		server_pid;
	t_sigaction	action;

	server_pid = getpid();
	ft_putnbr_fd(server_pid, 1);
	ft_putchar_fd('\n', 1);
	action.sa_sigaction = receive_char_signal;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (0);
}
