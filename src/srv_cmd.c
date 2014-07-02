/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 21:16:37 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/17 21:33:59 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "server.h"

int		read_cmd(char *cmd, char **pwd, int cs, char **envp)
{
	if (ft_strequ(cmd, "quit"))
		return (1);
	else if (ft_strequ(cmd, "pwd"))
		cmd_pwd(cs, *pwd);
	else if (ft_strnequ(cmd, "ls", 2))
		cmd_ls(cs, cmd);
	else if (ft_strnequ(cmd, "cd", 2))
		cmd_cd(cmd, pwd, cs, envp);
	else if (ft_strnequ(cmd, "get ", 4))
		cmd_get(cs, cmd);
	else if (ft_strnequ(cmd, "put ", 4))
		cmd_put(cs, cmd);
	return (0);
}
