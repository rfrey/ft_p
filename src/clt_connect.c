/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clt_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 20:39:34 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/16 18:30:49 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include "client.h"
#include "libft.h"
#include "ft_get_next_line.h"

int		create_client(char *ip, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
		return (-1);
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		return (-1);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(ip);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)))
	{
		ft_printf("connect error\n");
		return (-1);
	}
	ft_printf("Connection etablished at %s:%d\n", ip, port);
	return (sock);
}

void	prompt(int sock)
{
	int		ret;
	char	*line;

	while (42)
	{
		ft_printf("ftp > ");
		ret = ft_get_next_line(0, &line);
		if (ret < 1)
			return ;
		ft_putendl_fd(line, sock);
		ret = read_cmd(sock, line);
		free(line);
		if (ret)
			break ;
	}
}
