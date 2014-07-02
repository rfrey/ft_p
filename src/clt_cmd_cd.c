/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clt_cmd_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 16:33:49 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/16 16:43:58 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_get_next_line.h"
#include "libft.h"

void		cmd_cd(int sock)
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
