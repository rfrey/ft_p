/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clt_cmd_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 16:00:50 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/16 16:31:28 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_get_next_line.h"
#include "client.h"
#include "libft.h"

void		cmd_ls(int sock)
{
	char	*line;

	while (ft_get_next_line(sock, &line) == 1)
	{
		if (ft_strequ(line, ""))
			break ;
		ft_printf("%s\n", line);
		free(line);
	}
}
