/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cmd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 21:26:29 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/16 17:21:03 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cmd_pwd(int cs, char *pwd)
{
	ft_putstr_fd("SUCCESS : ", cs);
	ft_putendl_fd(pwd, cs);
	ft_putchar_fd(4, cs);
}
