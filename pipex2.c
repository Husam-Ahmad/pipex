/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:56:54 by huahmad           #+#    #+#             */
/*   Updated: 2025/03/18 13:11:29 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *find_path(char *cmd, char **envp)
{
    char **paths;
    char *thepath;
    int i;
    char *part;

    i = 0;
    while(ft_strnstr(envp[i], "PATH", 4) == 0)
        i++;
    paths = ft_split(envp[i] + 4, ':');
    i = 0;
    while(paths[i])
    {
        part = ft_strjoin(paths[i], "/");
        thepath = ft_strjoin(part, cmd);
        free(part);
        if (access(thepath, F_OK) == 0)
            return (thepath);
        free(thepath);
        i++;
    }
    i = -1;
    while (paths[++i])
        free(paths[i]);
    free(paths);
    return (0);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int 	i;
	char	*thepath;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	thepath = find_path(cmd[0], envp);
	if (!thepath)	
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		perror("error");
	}
	if (execve(thepath, cmd, envp) == -1)
		perror("error");
}
