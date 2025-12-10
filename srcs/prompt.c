/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:00:00 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 15:35:29 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_short_cwd(t_shell *shell)
{
	char	cwd[1024];
	char	*home;
	char	*short_path;
	int		len;

	if (!getcwd(cwd, 1024))
		return (ft_strdup("???"));
	home = env_get_value(shell->env, "HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		len = ft_strlen(home);
		short_path = ft_strjoin("~", cwd + len);
		return (short_path);
	}
	return (ft_strdup(cwd));
}

char	*get_prompt(t_shell *shell)
{
	char	*path;
	char	*prompt;
	char	*arrow;
	char	*temp;

	path = get_short_cwd(shell);
	if (shell->exit_code == 0)
		arrow = "\001\033[1;32m\002➜\001\033[0m\002";
	else
		arrow = "\001\033[1;31m\002➜\001\033[0m\002";
	temp = ft_strjoin(arrow, "  \001\033[1;34m\002");
	prompt = ft_strjoin(temp, path);
	free(temp);
	free(path);
	temp = ft_strjoin(prompt, "\001\033[0m\002 🖕$> ");
	free(prompt);
	return (temp);
}
