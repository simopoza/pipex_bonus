/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannahri <mannahri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:46:08 by mannahri          #+#    #+#             */
/*   Updated: 2022/02/23 10:55:50 by mannahri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child11_process(char	*av, int fd, char **env, t_p *t)
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
		dup2(fd, 0);
		dup2(t->pfd[0][1], STDOUT_FILENO);
		ft_close(t->ac - 5, t->pfd);
		execve(av2[0], av2, env);
		write(1, "This is not a command", 22);
	}
	free_lmlawi((void **)av2, i);
}

void	child22_process(char **av, char **env, int pfd[], t_p *t)
{
	int		fd;
	int		pid;
	char	**av3;
	int		i;

	i = 0;
	fd = open (av[t->ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	av3 = check_cmd(av[t->ac - 2], env);
	pid = fork();
	if (pid == -1)
		perror("second fork failed");
	if (pid == 0)
	{
		dup2 (pfd[0], STDIN_FILENO);
		dup2 (fd, STDOUT_FILENO);
		ft_close(t->ac - 5, t->pfd);
		execve(av3[0], av3, env);
		write(1, "This is not a command", 22);
	}
	free_lmlawi((void **)av3, i);
}
