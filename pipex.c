/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannahri <mannahri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 02:13:47 by mannahri          #+#    #+#             */
/*   Updated: 2022/02/23 10:02:46 by mannahri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int ac, int *pfd[])
{
	int	i;

	i = 0;
	while (i < ac)
	{
		close (pfd[i][0]);
		close (pfd[i][1]);
		i++;
	}
}

void	child1_process(char	*av, char *a, char **env, t_p *t)
{
	int		infile;
	char	**av2;
	int		pid;
	int		i;

	i = 0;
	infile = check_file(a);
	if (infile < 0)
		return ;
	av2 = check_cmd(av, env);
	pid = fork();
	if (pid == -1)
		perror("fork1 failed");
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(t->pfd[0][1], STDOUT_FILENO);
		ft_close(t->ac - 4, t->pfd);
		execve(av2[0], av2, env);
		write(1, "This is not a command", 22);
	}
	free_lmlawi((void **)av2, i);
}

void	child_middle_process(char	*av, char	**env, t_p *t, int p)
{
	char	**av2;
	int		pid;
	int		i;

	i = 0;
	av2 = check_cmd(av, env);
	pid = fork();
	if (pid == -1)
		perror("fork1 failed");
	if (pid == 0)
	{
		dup2(t->pfd[p - 1][0], STDIN_FILENO);
		dup2(t->pfd[p][1], STDOUT_FILENO);
		ft_close(t->ac - 4, t->pfd);
		execve(av2[0], av2, env);
		write(1, "This is not a command", 22);
	}
	free_lmlawi((void **)av2, i);
}

void	child2_process(char **av, char **env, int pfd[], t_p *t)
{
	int		outfile;
	int		pid;
	char	**av3;
	int		i;

	i = 0;
	outfile = make_file(av[t->ac - 1]);
	if (access(av[t->ac - 1], W_OK))
		exit(10);
	av3 = check_cmd(av[t->ac - 2], env);
	pid = fork();
	if (pid == -1)
		perror("second fork failed");
	if (pid == 0)
	{
		dup2 (pfd[0], STDIN_FILENO);
		dup2 (outfile, STDOUT_FILENO);
		ft_close(t->ac - 4, t->pfd);
		execve(av3[0], av3, env);
		write(1, "This is not a command", 22);
	}
	free_lmlawi((void **)av3, i);
}
