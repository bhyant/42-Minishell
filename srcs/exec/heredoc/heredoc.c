/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:24:49 by asmati            #+#    #+#             */
/*   Updated: 2025/11/30 14:24:49 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*clean_delimiter(char *delim)
{
	int	len;

	len = ft_strlen(delim);
	if (len >= 2 && ((delim[0] == '\'' && delim[len - 1] == '\'')
		|| (delim[0] == '"' && delim[len - 1] == '"')))
		return (ft_substr(delim, 1, len - 2));
	return (ft_strdup(delim));
}
static int	process_heredoc_line(char *line, char *delim, int fd, int expand, t_shell *shell)
{
	if(ft_strcmp(line, delim) == 0)
	{
		free(line);
		return (1);
	}
	if(expand)
	{
		line = expand_variables(line, shell->env, shell->exit_code);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (0);
}

static int	heredoc_loop(int fd, char *delimiter, int stdin_copy,int expand, t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if(g_signal == 130)
		{
			dup2 (stdin_copy, STDIN_FILENO);
			close (stdin_copy);
			return (-1);
		}
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", 2);
			break ;
		}
		if(process_heredoc_line(line, delimiter, fd, expand, shell))
			break;
	}
	close(stdin_copy);
	return (0);
}
static int	has_quotes(char *delim)
{
    int	len;

    len = ft_strlen(delim);
    if (len >= 2)
    {
        if ((delim[0] == '\'' && delim[len - 1] == '\'')
            || ((delim[0] == '"' && delim[len - 1] == '"')))
            return (0);  
    }
    return (1);  
}

int		handle_heredoc(char *delimiter, t_shell *shell)
{
	int		pipefd[2];
	int		stdin_copy;
	int		expand;
	char	*clean_delim;

	if (pipe(pipefd) == -1)
		return (-1);
	clean_delim = clean_delimiter(delimiter);
	stdin_copy = dup(STDIN_FILENO);
	signal_selector(2);
	expand = has_quotes(delimiter);
	if(heredoc_loop(pipefd[1], clean_delim, stdin_copy, expand, shell))
	{
		close(pipefd[0]);
		close(pipefd[1]);
		signal_selector(1);
		free(clean_delim);
		return (-1);
	}
	close(pipefd[1]);
	signal_selector(1);
	free(clean_delim);
	return (pipefd[0]);
}

