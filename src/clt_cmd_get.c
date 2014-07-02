/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clt_cmd_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 21:42:48 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/17 21:33:28 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "libft.h"
#include "ft_get_next_line.h"

#include <stdio.h>

int		get_fd(char *cmd, int sock)
{
	char			*filename;
	int				file;

	filename = &cmd[3];
	while (*filename == ' ')
		++filename;
	file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (file == -1)
	{
		ft_putendl("ERROR : can't create the file.");
		ft_putendl("Perhaps file already exists ?");
		ft_putendl_fd("FILE_ERROR", sock);
	}
	else
		ft_putendl_fd("FILE_OK", sock);
	return (file);
}

void	recv_file(int sock, int file, int totsize)
{
	char			*buf;
	int				size;
	int				n;

	ft_putendl("Downloading in progress. Please wait...");
	n = 0;
	buf = malloc(sizeof(char) * totsize);
	while (n < totsize)
	{
		size = recv(sock, buf + n, 4096, 0);
		n += size;
	}
	write(file, buf, totsize);
}

int		wait_msg(char *msg, int fd)
{
	char		*input;
	int			ret;

	input = NULL;
	if (ft_get_next_line(fd, &input) == -1)
		return (-1);
	ret = ft_strequ(input, msg);
	free(input);
	return (ret);
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

int		cmd_get(int sock, char *cmd)
{
	int		file;
	int		size;
	char	*line;

	if (wait_msg("FILE_SRV_OK", sock) < 1)
	{
		ft_putendl("ERROR : can't access/found this file");
		return (-1);
	}
	if ((file = get_fd(cmd, sock)) == -1)
		return (-1);
	if ((size = get_filesize(sock)) == -1)
		return (-1);
	recv_file(sock, file, size);
	ft_putendl_fd("SUCCESS", sock);
	if (ft_get_next_line(sock, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
	close(file);
	return (0);
}
