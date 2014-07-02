/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clt_cmd_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 20:58:38 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/17 21:33:39 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "client.h"
#include "ft_get_next_line.h"

int		send_error(int cs, char *msg)
{
	ft_putendl_fd(msg, cs);
	return (-1);
}

int		get_file(char *cmd, int cs)
{
	char		*filename;
	int			file;

	filename = &cmd[3];
	while (*filename == ' ')
		++filename;
	if ((file = open(filename, O_RDONLY)) == -1)
	{
		ft_putendl("ERROR : can't access/found this file");
		send_error(cs, "FILE_ERROR");
	}
	else
		send_error(cs, "FILE_CLT_OK");
	return (file);
}

int		handle_put(struct stat buf, int cs, void *ptr, int file)
{
	char		*totsize;

	totsize = ft_itoa(buf.st_size);
	ft_putendl_fd(totsize, cs);
	free(totsize);
	if (wait_msg("GO_SEND", cs) < 1)
		return (1);
	ft_putendl("Uploading in progress. Please wait...");
	send(cs, ptr, buf.st_size, 0);
	munmap(ptr, buf.st_size);
	close(file);
	if (wait_msg("SUCCESS", cs) == 1)
		ft_putendl("SUCCESS : file transfert complete.");
	return (0);
}

int		cmd_put(int cs, char *cmd)
{
	int			file;
	struct stat	buf;
	void		*ptr;

	if ((file = get_file(cmd, cs)) == -1)
		return (-1);
	if (wait_msg("FILE_OK", cs) < 1)
	{
		ft_putendl("ERROR : can't create the file.");
		ft_putendl("Perhaps file already exists ?");
		return (-1);
	}
	if ((fstat(file, &buf)) == -1)
	{
		ft_putendl("ERROR : fstat().");
		return (-1);
	}
	if ((ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl("ERROR server : mmap().");
		return (-1);
	}
	return (handle_put(buf, cs, ptr, file));
}
