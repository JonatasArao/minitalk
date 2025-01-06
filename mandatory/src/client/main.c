/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:03:03 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/06 13:37:16 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static pid_t	get_server_pid(int argc, char **argv)
{
	long	server_pid;
	char	*endptr;

	if (argc != 3)
	{
		ft_putendl_fd("Usage : ./client <server_pid> <string_to_send>", 2);
		return (-1);
	}
	if (!ft_strall(argv[1], ft_isdigit))
	{
		ft_putendl_fd("Error: Server PID must contain only digits.", 2);
		return (-1);
	}
	server_pid = ft_strtol(argv[1], &endptr, 10);
	if (server_pid > INT_MAX || *endptr != '\0')
	{
		ft_putendl_fd("Error: Invalid Server PID.", 2);
		return (-1);
	}
	return ((pid_t) server_pid);
}

int	send_char_signal(char c, pid_t server_pid)
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
		usleep(500);
	}
	return (0);
}

int	send_string_signal(char *str, pid_t server_pid)
{
	while (*str)
	{
		if (send_char_signal(*str++, server_pid) == -1)
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	server_pid = get_server_pid(argc, argv);
	if (server_pid == -1)
		return (1);
	ft_putendl_fd("Minitalk Client", 1);
	return (send_string_signal(argv[2], server_pid));
}
