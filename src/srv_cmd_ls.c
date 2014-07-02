/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cmd_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 22:31:18 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/16 18:27:36 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "libft.h"

void	cmd_ls(int cs, char *cmd)
{
	pid_t	pid;
	char	**args;

	pid = fork();
	if (pid == 0)
	{
		args = ft_strsplit(cmd, ' ');
		dup2(cs, STDOUT_FILENO);
		dup2(cs, STDERR_FILENO);
		execv("/bin/ls", args);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		wait4(pid, NULL, 0, 0);
		ft_putendl_fd("", cs);
	}
}
