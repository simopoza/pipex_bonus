/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannahri <mannahri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 04:39:29 by mannahri          #+#    #+#             */
/*   Updated: 2022/02/23 10:02:54 by mannahri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_process_man(char	*av, char	*a, char	**env, int pfd[])
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
		close(pfd[0]);
		dup2(infile, STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		execve(av2[0], av2, env);
		perror("This is not a command");
	}
	free_lmlawi((void **)av2, i);
}

void	child2_process_man(char *av, char *a, char **env, int pfd[])
{
	int		outfile;
	int		pid;
	char	**av3;
	int		i;

	i = 0;
	outfile = make_file(a);
	if (access(a, W_OK))
		return ;
	av3 = check_cmd(av, env);
	pid = fork();
	if (pid == -1)
		perror("second fork failed");
	if (pid == 0)
	{
		close (pfd[1]);
		dup2 (pfd[0], STDIN_FILENO);
		dup2 (outfile, STDOUT_FILENO);
		execve(av3[0], av3, env);
		perror ("This is not a command");
	}
	free_lmlawi((void **)av3, i);
}
