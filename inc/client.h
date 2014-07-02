/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 16:55:21 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/17 21:10:07 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

int		read_cmd(int sock, char *cmd);
int		create_client(char *ip, int port);
void	prompt(int sock);

int		wait_msg(char *msg, int fd);

void	cmd_pwd(int sock);
void	cmd_ls(int sock);
void	cmd_cd(int sock);
void	cmd_get(int sock, char *cmd);
int		cmd_put(int sock, char *cmd);

#endif
