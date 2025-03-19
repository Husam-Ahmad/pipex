/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:50:56 by huahmad           #+#    #+#             */
/*   Updated: 2025/03/17 19:22:15 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// so the child process that run inside the fork takes the filein, puts the output 
// inside a pipe and then closes the input so it doesn't have to wait for 
// info from the other side and then closes with the exec function. something like that.
// STDOUT_FILENO == 1
void child_process(char **argv, char **envp, int *fd)
{
    int filein;
    
    filein = open(argv[1], O_RDONLY, 0777);
    if (filein == -1)
        perror("error");
    dup2(fd[1], STDOUT_FILENO);
    dup2(filein, 0);
    close(fd[0]);
    execute(argv[2], envp);    
}

// and the parent process takes the data from the pipe, chandges the output for the fileout 
// and then closes with the exec thing
void parent_process(char **argv, char **envp, int *fd)
{
    int fileout;
    
    fileout = open(argv[4], O_WRONLY | O_CREAT |  O_TRUNC, 0777);
    if (fileout == -1)
        perror("error");
    dup2(fd[0], STDIN_FILENO);
    dup2(fileout, STDOUT_FILENO);
    close(fd[1]);
    execute(argv[3], envp);
}

int main(int argc, char **argv, char **envp)
{
    int fd[2];
    pid_t pid1;

    if (argc == 5)
    {
        if (pipe(fd) == -1)
            perror("error");
        pid1 = fork();
        if (pid1 == -1)
            perror("error");
        if (pid1 == 0)
            child_process(argv, envp, fd);
        waitpid(pid1, NULL, 0);
        parent_process(argv, envp, fd);
    }
    else
    {
        ft_putstr_fd("wrong arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
    }
}