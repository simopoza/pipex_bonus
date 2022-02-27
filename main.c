/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannahri <mannahri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 02:17:13 by mannahri          #+#    #+#             */
/*   Updated: 2022/02/23 11:44:16 by mannahri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**ft_helper(char **av, char **env, int ac)
{
	t_p	t;
	int	i;

	t.ac = ac;
	i = 0;
	t.pfd = (int **)malloc(sizeof(int *) * (t.ac - 4));
	if (!t.pfd)
		return (0);
	while (i < t.ac - 4)
	{
		t.pfd[i] = (int *)malloc(sizeof(int) * 2);
		pipe(t.pfd[i]);
		i++;
	}
	child1_process (av[2], av[1], env, &t);
	i = 3;
	while (i < t.ac - 2)
	{
		child_middle_process (av[i], env, &t, i - 2);
		i++;
	}
	child2_process(av, env, t.pfd[ac - 5], &t);
	return (t.pfd);
}

int	main(int ac, char *av[], char *env[])
{
	t_p	t;

	t.ac = ac;
	if (t.ac < 5)
		exit (0);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		t.pfd = ft_help_herdoc(av, env, ac);
		ft_close(t.ac - 5, t.pfd);
	}
	else
	{
		t.pfd = ft_helper(av, env, ac);
		ft_close(t.ac - 4, t.pfd);
	}
	while (wait(NULL) != -1)
	{
	}
	return (0);
}
