/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:04:37 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/07 15:17:40 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	collect_and_print_string(char c)
{
	static char	*string = NULL;
	char		c_string[2];
	char		*temp;

	if (!string)
		string = ft_strdup("");
	if (c && string)
	{
		c_string[0] = c;
		c_string[1] = '\0';
		temp = ft_strjoin(string, c_string);
		if (!temp)
			ft_delpointer((void **)&string);
		free(string);
		string = temp;
	}
	else
	{
		if (*string)
			ft_putendl_fd(string, 1);
		ft_delpointer((void **)&string);
	}
}

void	receive_char_signal(int sig, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		bit_count = 0;
	pid_t			client_pid;

	(void) context;
	client_pid = info->si_pid;
	if (sig == SIGUSR1)
		c &= ~(1 << bit_count);
	else if (sig == SIGUSR2)
		c |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		collect_and_print_string(c);
		c = 0;
		bit_count = 0;
	}
	if (kill(client_pid, sig) == -1)
	{
		collect_and_print_string('\0');
		ft_putendl_fd("Error: client disconnected.", 2);
		c = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	pid_t		server_pid;
	t_sigaction	action;

	server_pid = getpid();
	ft_putstr_fd("Minitalk Server - PID: ", 1);
	ft_putnbr_fd(server_pid, 1);
	ft_putchar_fd('\n', 1);
	action.sa_sigaction = receive_char_signal;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
