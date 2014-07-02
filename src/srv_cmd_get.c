/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cmd_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 21:31:54 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/17 21:34:17 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_get_next_line.h"

int		send_error(int cs, char *msg)
{
	ft_putendl_fd(msg, cs);
	return (-1);
}

int		get_fd(char *cmd, int cs)
{
	char		*filename;
	int			file;

	filename = &cmd[3];
	while (*filename == ' ')
		++filename;
	if ((file = open(filename, O_RDONLY)) == -1)
		send_error(cs, "FILE_ERROR");
	else
		send_error(cs, "FILE_SRV_OK");
	return (file);
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

int		cmd_get(int cs, char *cmd)
{
	int			file;
	struct stat	buf;
	void		*ptr;
	char		*totsize;

	if ((file = get_fd(cmd, cs)) == -1)
		return (-1);
	if (wait_msg("FILE_OK", cs) < 1)
		return (1);
	if ((fstat(file, &buf)) == -1)
		return (send_error(cs, "ERROR server : fstat()."));
	if ((ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
		return (send_error(cs, "ERROR server : mmap()."));
	totsize = ft_itoa(buf.st_size);
	ft_putendl_fd(totsize, cs);
	free(totsize);
	if (wait_msg("GO_SEND", cs) < 1)
		return (1);
	send(cs, ptr, buf.st_size, 0);
	munmap(ptr, buf.st_size);
	close(file);
	if (wait_msg("SUCCESS", cs) == 1)
		send_error(cs, "SUCCESS : file transfert complete.");
	return (0);
}
