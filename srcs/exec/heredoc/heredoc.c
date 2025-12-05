/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:18:51 by asmati            #+#    #+#             */
/*   Updated: 2025/12/02 17:18:51 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_heredoc
{
	int		fd;
	char	*delimiter;
	int		expand;
	t_shell	*shell;
}	t_heredoc;

static char	*clean_delimiter(char *delim)
{
	int	len;

	len = ft_strlen(delim);
	if (len >= 2 && ((delim[0] == '\'' && delim[len - 1] == '\'')
			|| (delim[0] == '"' && delim[len - 1] == '"')))
		return (ft_substr(delim, 1, len - 2));
	return (ft_strdup(delim));
}

static int	process_heredoc_line(char *line, t_heredoc *data)
{
	char	*tmp;

	if (ft_strcmp(line, data->delimiter) == 0)
		return (free(line), 1);
	if (data->expand)
	{
		tmp = line;
		line = expand_variables(line, data->shell->env, data->shell->exit_code);
		free(tmp);
	}
	write(data->fd, line, ft_strlen(line));
	write(data->fd, "\n", 1);
	return (free(line), 0);
}

static int	heredoc_loop(t_heredoc *data, int stdin_copy)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == 130)
		{
			data->shell->exit_code = 130;
			dup2(stdin_copy, STDIN_FILENO);
			close(stdin_copy);
			free(line);
			return (-1);
		}
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", 2);
			break ;
		}
		if (process_heredoc_line(line, data))
			break ;
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
		if ((delim[0] == '\'' && delim[len - 1] == '\'') || ((delim[0] == '"'
					&& delim[len - 1] == '"')))
			return (0);
	}
	return (1);
}

int	handle_heredoc(char *delimiter, t_shell *shell)
{
	int			pipefd[2];
	int			stdin_copy;
	char		*clean_delim;
	t_heredoc	data;

	if (pipe(pipefd) == -1)
		return (-1);
	clean_delim = clean_delimiter(delimiter);
	stdin_copy = dup(STDIN_FILENO);
	signal_selector(2);
	data.fd = pipefd[1];
	data.delimiter = clean_delim;
	data.expand = has_quotes(delimiter);
	data.shell = shell;
	if (heredoc_loop(&data, stdin_copy))
	{
		close(pipefd[0]);
		close(pipefd[1]);
		signal_selector(1);
		free(clean_delim);
		return (-1);
	}
	return (close(pipefd[1]), signal_selector(1), free(clean_delim), pipefd[0]);
}
