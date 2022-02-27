/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannahri <mannahri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:45:31 by mannahri          #+#    #+#             */
/*   Updated: 2022/02/23 11:44:31 by mannahri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_herdoc(char *av, int fd)
{
	char	*av1;
	char	*av2;

	av1 = malloc(1);
	if (!av1)
		return ;
	av2 = ft_strjoin(av, "\n");
	while (ft_strcmp (av1, av2))
	{
		if (av1)
			ft_putstr_fd(av1, fd);
		free (av1);
		av1 = get_next_line(0);
	}
	free (av1);
	free (av2);
	close (fd);
}

int	make_it(char **av)
{
	int	fd;

	fd = open("/tmp/in", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		perror ("error");
	ft_herdoc(av[2], fd);
	fd = open("/tmp/in", O_RDONLY, 0644);
	return (fd);
}

int	**ft_help_herdoc(char **av, char **env, int ac)
{
	t_p	t;
	int	i;
	int	fd;

	t.ac = ac;
	i = 0;
	t.pfd = (int **)malloc(sizeof(int *) * (t.ac - 5));
	if (!t.pfd)
		return (0);
	while (i < t.ac - 5)
	{
		t.pfd[i] = (int *)malloc(sizeof(int) * 2);
		pipe(t.pfd[i]);
		i++;
	}
	fd = make_it(av);
	child11_process (av[3], fd, env, &t);
	i = 4;
	while (i < t.ac - 2)
	{
		child_middle_process (av[i], env, &t, i - 3);
		i++;
	}
	child22_process(av, env, t.pfd[t.ac - 6], &t);
	return (t.pfd);
}
