/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clt_cmd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 21:45:30 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/14 22:36:22 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_get_next_line.h"
#include "client.h"
#include "libft.h"

void		cmd_pwd(int sock)
{
	char	*line;

	if (ft_get_next_line(sock, &line) == 1)
	{
		ft_printf("%s\n", line);
		free(line);
	}
}
