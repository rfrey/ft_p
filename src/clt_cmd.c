/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clt_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 20:28:16 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/17 21:01:11 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "client.h"

void	cmd_unknow(char *cmd)
{
	ft_printf("ERROR : unknow command : '%s'.\n", cmd);
}

int		read_cmd(int sock, char *cmd)
{
	if (ft_strequ(cmd, "quit"))
		return (1);
	else if (ft_strequ(cmd, "pwd"))
		cmd_pwd(sock);
	else if (ft_strnequ(cmd, "ls", 2))
		cmd_ls(sock);
	else if (ft_strnequ(cmd, "cd", 2))
		cmd_cd(sock);
	else if (ft_strnequ(cmd, "get ", 4))
		cmd_get(sock, cmd);
	else if (ft_strnequ(cmd, "put ", 4))
		cmd_put(sock, cmd);
	else
		cmd_unknow(cmd);
	return (0);
}
