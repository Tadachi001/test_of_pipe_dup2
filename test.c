/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravelon <mravelon@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:39:15 by mravelon          #+#    #+#             */
/*   Updated: 2024/09/08 17:08:00 by mravelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main()
{
	int pipefd[2];
	pid_t pid_1, pid_2;


	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	pid_1 = fork();
	if (pid_1 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid_1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		char *argv1[] = {"ls", NULL};
		execve("/usr/bin/ls", argv1, NULL);
		perror("execve");
		exit(1);
	}
	if (pid_2 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid_2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		
		char *argv2[] = {"wc", NULL};
		execve("/usr/bin/wc", argv2, NULL);
		perror("execve");
		exit(1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
