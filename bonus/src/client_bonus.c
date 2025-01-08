/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:03:03 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/08 12:57:50 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static volatile sig_atomic_t	g_echo = 0;

static pid_t	get_server_pid(int argc, char **argv)
{
	long	server_pid;
	char	*endptr;

	if (argc != 3)
	{
		ft_putendl_fd("Usage : ./client <server_pid> <string_to_send>", 2);
		exit(EXIT_FAILURE);
	}
	if (!ft_strall(argv[1], ft_isdigit))
	{
		ft_putendl_fd("Error: Server PID must contain only digits.", 2);
		exit(EXIT_FAILURE);
	}
	server_pid = ft_strtol(argv[1], &endptr, 10);
	if (server_pid > INT_MAX || *endptr != '\0')
	{
		ft_putendl_fd("Error: Invalid Server PID.", 2);
		exit(EXIT_FAILURE);
	}
	return ((pid_t) server_pid);
}

static void	receive_server_response(int sig)
{
	if (sig == SIGUSR1 || sig == SIGUSR2)
		g_echo = sig;
}

static int	timeout_server(int timeout)
{
	while (!g_echo && timeout > 0)
	{
		usleep(250);
		timeout -= 250;
	}
	if (timeout <= 0)
		return (-1);
	if (g_echo)
		g_echo = 0;
	return (0);
}

static int	send_char_signal(char c, pid_t server_pid)
{
	int		bit_count;
	int		signal;

	bit_count = 0;
	while (bit_count < 8)
	{
		if ((c >> bit_count) & 1)
			signal = SIGUSR2;
		else
			signal = SIGUSR1;
		if (kill(server_pid, signal) == -1)
		{
			ft_putendl_fd("Error: Unable to send signal.", 2);
			return (-1);
		}
		bit_count++;
		if (timeout_server(500000) == -1)
		{
			ft_putendl_fd("Error: Server response timeout.", 2);
			return (-1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t		server_pid;
	t_sigaction	action;

	ft_putstr_fd("Minitalk Client - ", 1);
	server_pid = get_server_pid(argc, argv);
	action.sa_handler = receive_server_response;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (*argv[2])
	{
		if (send_char_signal(*argv[2]++, server_pid) == -1)
			return (EXIT_FAILURE);
	}
	if (send_char_signal('\0', server_pid) == -1)
		return (EXIT_FAILURE);
	ft_putendl_fd("Message sent successfully.", 1);
	return (EXIT_SUCCESS);
}
