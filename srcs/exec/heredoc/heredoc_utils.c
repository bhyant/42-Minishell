/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:00:00 by asmati            #+#    #+#             */
/*   Updated: 2025/12/10 14:56:51 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_heredocs(t_command *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			fd = handle_heredoc(redir->file, shell);
			if (fd == -1)
			{
				close_heredocs(cmd);
				return (-1);
			}
			redir->heredoc_fd = fd;
		}
		else
			redir->heredoc_fd = -1;
		redir = redir->next;
	}
	return (0);
}

void	close_heredocs(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == HEREDOC && redir->heredoc_fd != -1)
		{
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		redir = redir->next;
	}
}

void	close_all_heredocs(t_shell *shell)
{
	t_command	*cmd;

	cmd = shell->command;
	while (cmd)
	{
		close_heredocs(cmd);
		cmd = cmd->next;
	}
}
