/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_cmd_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 16:36:46 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/17 19:15:36 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "list.h"

static char		*ft_gen_path_from_list(t_list *list, char *path)
{
	int			i;
	char		*tmp;

	i = 0;
	if (!list)
		path[0] = '/';
	while (list)
	{
		path[i] = '/';
		i++;
		tmp = (char *)ft_listpoplast(&list);
		ft_strcat(&path[i], tmp);
		free(tmp);
		i = ft_strlen(path);
	}
	return (path);
}

char			*ft_catpath(char *path_l, char *path_r)
{
	int			len;
	char		*fullpath;

	len = 1 + ft_strlen(path_l) + ft_strlen(path_r);
	if (!((fullpath = ft_strnew(len))))
		return (NULL);
	ft_strcpy(fullpath, path_l);
	ft_strcat(fullpath, "/");
	ft_strcat(fullpath, path_r);
	return (fullpath);
}

void			ft_path_canonize(char **path)
{
	int			i;
	char		*new;
	char		**tab;
	t_list		*list;

	new = ft_strnew(ft_strlen(*path));
	tab = ft_strsplit(*path, '/');
	list = NULL;
	i = 0;
	while (tab[i])
	{
		if (!ft_strequ(tab[i], "."))
		{
			if (ft_strequ(tab[i], ".."))
			{
				if (list)
					free(ft_listpop(&list));
			}
			else if (!ft_strequ(tab[i], ""))
				ft_listpushfront(&list, ft_strdup(tab[i]));
		}
		i++;
	}
	ft_strtabfree(&tab);
	*path = ft_gen_path_from_list(list, new);
}

char			*get_cd_arg(char *cmd)
{
	int	i;

	i = 2;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (&cmd[i]);
		++i;
	}
	return (cmd);
}

void			cmd_cd(char *cmd, char **pwd, int cs, char **envp)
{
	char	*arg;
	char	*dir;
	char	*srv_pwd;

	if (!((srv_pwd = ft_getenv(envp, "PWD"))))
		srv_pwd = "";
	arg = get_cd_arg(cmd);
	if (arg[0] != '/')
		dir = ft_catpath(*pwd, arg);
	else
		dir = ft_strdup(arg);
	ft_path_canonize(&dir);
	if (!ft_strnequ(srv_pwd, dir, ft_strlen(srv_pwd)) || chdir(dir))
	{
		ft_putstr_fd("ERROR ! Can't access this directory : ", cs);
		ft_putendl_fd(dir, cs);
	}
	else
	{
		ft_putstr_fd("SUCCESS : ", cs);
		ft_putendl_fd(dir, cs);
		free(*pwd);
		*pwd = dir;
	}
	ft_putendl_fd("", cs);
}
