/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cmd_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 20:58:10 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/17 21:26:24 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "libft.h"
#include "server.h"
#include "ft_get_next_line.h"

#include <stdio.h>

int		get_file(char *cmd, int sock)
{
	char			*filename;
	int				file;

	filename = &cmd[3];
	while (*filename == ' ')
		++filename;
	file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (file == -1)
		ft_putendl_fd("FILE_ERROR", sock);
	else
		ft_putendl_fd("FILE_OK", sock);
	return (file);
}

void	recv_file(int sock, int file, int totsize)
{
	char			*buf;
	int				size;
	int				n;

	n = 0;
	buf = malloc(sizeof(char) * totsize);
	while (n < totsize)
	{
		size = recv(sock, buf + n, 4096, 0);
		n += size;
	}
	write(file, buf, totsize);
}

int		get_filesize(int sock)
{
	int		size;
	char	*line;

	size = 0;
	if (ft_get_next_line(sock, &line) == 1)
	{
		size = ft_atoi(line);
		if (size < 1)
		{
			ft_putendl(line);
			ft_putendl_fd("ERROR_FILESIZE", sock);
			free(line);
			return (-1);
		}
		free(line);
	}
	else
		return (-1);
	ft_putendl_fd("GO_SEND", sock);
	return (size);
}

int		cmd_put(int sock, char *cmd)
{
	int		file;
	int		size;

	if (wait_msg("FILE_CLT_OK", sock) < 1)
		return (-1);
	if ((file = get_file(cmd, sock)) == -1)
		return (-1);
	if ((size = get_filesize(sock)) == -1)
		return (-1);
	recv_file(sock, file, size);
	ft_putendl_fd("SUCCESS", sock);
	close(file);
	return (0);
}
