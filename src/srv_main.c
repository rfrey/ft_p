/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 16:37:24 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/16 18:33:58 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "server.h"

int		main(int argc, char **argv, char **envp)
{
	int	sock;

	if (argc == 2)
		sock = create_serveur(ft_atoi(argv[1]));
	else
		return (ft_printf("usage : %s port\n", argv[0]));
	if (sock == -1)
		return (1);
	wait_connect(sock, envp);
	close(sock);
	return (0);
}
