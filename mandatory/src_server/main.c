/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:04:37 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/03 15:09:06 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive_char_signal(int sig)
{
	if (sig == SIGUSR1)
		ft_putnbr_fd(0, 1);
	else if (sig == SIGUSR2)
		ft_putnbr_fd(1, 1);
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	s_sa;

	server_pid = getpid();
	ft_putnbr_fd(server_pid, 1);
	ft_putchar_fd('\n', 1);
	s_sa.sa_handler = receive_char_signal;
	sigemptyset(&s_sa.sa_mask);
	s_sa.sa_flags = 0;
	sigaction(SIGUSR1, &s_sa, NULL);
	sigaction(SIGUSR2, &s_sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
