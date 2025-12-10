/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:36:39 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 15:13:23 by tbhuiyan         ###   ########.fr       */
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

void	shell_cleanup(t_shell *shell)
{
	if (shell->env)
		free_env(shell->env);
	if (shell->envp)
		free_envp(shell->envp);
	if (shell->token)
		ft_tokenclear(&shell->token);
	if (shell->command)
		free_command(shell->command);
	if (shell->entry)
	{
		free(shell->entry);
		shell->entry = NULL;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	loop_readline(t_shell *shell)
{
	char	*prompt_str;

	while (1)
	{
		g_signal = 0;
		signal_selector(1);
		prompt_str = get_prompt(shell);
		shell->entry = readline(prompt_str);
		free(prompt_str);
		if (!shell->entry)
		{
			printf("exit\n");
			break ;
		}
		if (g_signal == 130)
			shell->exit_code = 130;
		if (shell->entry[0] != '\0')
			add_history(shell->entry);
		if (!parsing(shell->entry, shell))
		{
			shell->exit_code = 2;
			free(shell->entry);
			shell->entry = NULL;
			continue ;
		}
		else
			execute_and_cleanup(shell);
		cleanup_iteration(shell);
		if (shell->entry)
		{
			free(shell->entry);
			shell->entry = NULL;
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	signal(SIGPIPE, SIG_IGN);
	print_welcome_msg();
	print_welcome_msg2();
	if (!init_shell(&shell, envp))
		return (ft_putstr_fd("Error : Failed to initialize shell",
				STDERR_FILENO), 1);
	loop_readline(&shell);
	shell_cleanup(&shell);
	return (shell.exit_code);
}
