/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:03:03 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/03 09:36:20 by jarao-de         ###   ########.fr       */
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
	if (kill(server_pid, SIGUSR1) == -1)
	{
		ft_putendl_fd("Error: No such process or permission denied.", 2);
		return (-1);
	}
	return ((pid_t) server_pid);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	server_pid = get_server_pid(argc, argv);
	if (server_pid == -1)
		return (1);
	ft_putendl_fd("Minitalk Client", 1);
	return (0);
}
