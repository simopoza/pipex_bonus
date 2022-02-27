/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannahri <mannahri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 01:47:49 by mannahri          #+#    #+#             */
/*   Updated: 2022/02/23 10:30:35 by mannahri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_pipe{
	char	**path_splited;
	char	**path;
	char	**help;
	char	*r;
	int		i;
}	t_mypath;

typedef struct s_help{
	int		ac;
	int		**pfd;
}	t_p;

char	*ft_strjoin1(char *s1, char *s2);
char	*get_next_line(int fd);
void	free_lmlawi(void **mlawi, int i);
char	**split_path(char *s, char c);
char	*ft_substr(char *s, int start, size_t len);
int		ft_strlen(char	*s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	**check_cmd(char *str, char *env[]);
int		check_file(char *str);
int		make_file(char *str);
void	ft_close(int ac, int *pfd[]);
int		**ft_helper(char **av, char **env, int ac);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_herdoc(char *av, int fd);
int		**ft_help_herdoc(char **av, char **env, int ac);
void	child11_process(char	*av, int fd, char **env, t_p *t);
void	child22_process(char **av, char **env, int pfd[], t_p *t);
void	child1_process(char	*av, char *a, char **env, t_p *t);
void	child_middle_process(char	*av, char	**env, t_p *t, int p);
void	child2_process(char **av, char **env, int pfd[], t_p *t);
void	child1_process_man(char	*av, char	*a, char	**env, int pfd[]);
void	child2_process_man(char *av, char *a, char **env, int pfd[]);
int		main(int ac, char *av[], char *env[]);

#endif