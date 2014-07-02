/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 21:12:09 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/16 18:35:30 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_get_next_line.h"
#include "server.h"
#include "libft.h"

int		create_serveur(int port)
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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)))
	{
		ft_printf("bind error\n");
		return (-1);
	}
	listen(sock, 42);
	ft_printf("Server run on port %d.\n", port);
	return (sock);
}

void	handle_ftp(int cs, struct sockaddr_in csin, char **envp)
{
	int		ret;
	char	*cmd;
	char	*pwd;

	pwd = ft_strdup(ft_getenv(envp, "PWD"));
	ft_printf("%s:%d connected\n", inet_ntoa(csin.sin_addr), csin.sin_port);
	while (42)
	{
		ret = ft_get_next_line(cs, &cmd);
		if (ret > 0)
		{
			ft_printf("%s:%d > %s\n", inet_ntoa(csin.sin_addr),
										csin.sin_port, cmd);
			if (read_cmd(cmd, &pwd, cs, envp))
				break ;
			free(cmd);
		}
		else
			break ;
	}
	ft_printf("%s:%d disconnected\n", inet_ntoa(csin.sin_addr), csin.sin_port);
	free(pwd);
	close(cs);
}

void	wait_connect(int sock, char **envp)
{
	int					cs;
	struct sockaddr_in	csin;
	unsigned int		cslen;
	pid_t				pid;

	while (42)
	{
		cs = accept(sock, (struct sockaddr *)&csin, &cslen);
		pid = fork();
		if (pid == 0)
		{
			handle_ftp(cs, csin, envp);
			break ;
		}
		close(cs);
	}
}
