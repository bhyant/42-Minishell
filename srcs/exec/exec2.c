/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:00:00 by asmati            #+#    #+#             */
/*   Updated: 2025/12/04 21:30:29 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_redir_file(t_redir *redir)
{
	int	fd;

	if (redir->type == HEREDOC)
		fd = redir->heredoc_fd;
	else if (redir->type == IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -2;
	return (fd);
}

int	apply_redir_fd(t_redir *redir, int fd)
{
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	if (redir->type == IN || redir->type == HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	if (redir->type != HEREDOC)
		close(fd);
	return (0);
}
