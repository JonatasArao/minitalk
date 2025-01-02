/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:03:03 by jarao-de          #+#    #+#             */
/*   Updated: 2025/01/02 17:39:38 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	get_server_pid(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putendl_fd("Usage : ./client <server_pid> <string_to_send>", 2);
		return (0);
	}
	if (!ft_strall(argv[1], ft_isdigit))
	{
		ft_putendl_fd("Error: PID must be a valid value.", 2);
		return (0);
	}
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, SIGUSR1) == -1 || kill(server_pid, SIGUSR2) == -1)
	{
		ft_putendl_fd("Error: No such process or permission denied.", 2);
		return (0);
	}
	return (server_pid);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	server_pid = get_server_pid(argc, argv);
	if (!server_pid)
		return (1);
	ft_putendl_fd("Minitalk Client", 1);
	return (0);
}
