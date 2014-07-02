/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 16:54:51 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/17 21:11:46 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <netinet/in.h>

int		create_serveur(int port);
void	wait_connect(int sock, char **envp);

int		read_cmd(char *cmd, char **pwd, int cs, char **envp);
int		wait_msg(char *msg, int fd);

void	cmd_ls(int cs, char *cmd);
void	cmd_pwd(int cs, char *pwd);
void	cmd_cd(char *cmd, char **pwd, int cs, char **envp);
int		cmd_get(int cs, char *cmd);
int		cmd_put(int cs, char *cmd);

#endif
