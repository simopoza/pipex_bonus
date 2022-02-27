/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannahri <mannahri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 02:16:02 by mannahri          #+#    #+#             */
/*   Updated: 2022/02/23 10:27:57 by mannahri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char *path[])
{
	char	**s2;
	char	*s;
	int		i;

	i = 0;
	while (path[i])
	{
		if (!ft_strncmp(path[i], "PATH=", 4))
		{
			s = ft_substr(path[i], 5, ft_strlen(path[i]));
			s2 = split_path(s, ':');
			free (s);
			return (s2);
		}
		i++;
	}
	return (NULL);
}

void	free_lmlawi(void	**mlawi, int i)
{
	while (mlawi[i])
	{
		free (mlawi[i]);
		i++;
	}
	free (mlawi);
}

void	inital(t_mypath *t, char *str, char *env[])
{
	t->i = -1;
	t->path_splited = find_path(env);
	t->path = split_path(str, ' ');
	t->help = t->path_splited;
}

char	**check_cmd(char *str, char *env[])
{
	t_mypath	*t;

	t = malloc(sizeof(t_mypath));
	if (!t)
		return (0);
	inital(t, str, env);
	while (t->path_splited[++t->i])
	{
		free (t->help[t->i]);
		t->path_splited[t->i] = ft_strjoin(t->path_splited[t->i], "/");
		t->r = ft_strjoin(t->path_splited[t->i], t->path[0]);
		free (t->path_splited[t->i]);
		if (!access(t->r, X_OK))
		{
			free (t->path[0]);
			t->path[0] = t->r;
			free_lmlawi((void **)t->help, ++t->i);
			free (t);
			return (t->path);
		}
		free (t->r);
	}
	free (t->path_splited);
	free (t);
	return (t->path);
}
