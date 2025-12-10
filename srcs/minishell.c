/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:36:39 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 12:18:50 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Ajoute <unistd.h> pour usleep si tu ne l'as pas */

// Fonction pour raccourcir le chemin (remplacer /home/user par ~)
static char *get_short_cwd(t_shell *shell)
{
    char    cwd[1024];
    char    *home;
    char    *short_path;
    int     len;

    if (!getcwd(cwd, 1024))
        return (ft_strdup("???"));
    
    home = env_get_value(shell->env, "HOME");
    if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
    {
        // On remplace le début par ~
        len = ft_strlen(home);
        short_path = ft_strjoin("~", cwd + len);
        return (short_path);
    }
    return (ft_strdup(cwd));
}

char *get_prompt(t_shell *shell)
{
    char    *path;
    char    *prompt;
    char    *arrow;
    char    *temp;

    path = get_short_cwd(shell);
    
    // Si la dernière commande a réussi (0) -> Vert, sinon -> Rouge
    if (shell->exit_code == 0)
        arrow = "\001\033[1;32m\002➜\001\033[0m\002"; // Vert
    else
        arrow = "\001\033[1;31m\002➜\001\033[0m\002"; // Rouge

    // Construction : "➜ path $> "
    // Note : \001 et \002 disent à readline "ceci est une couleur, ne compte pas la longueur"
    
    // Etape 1 : Arrow + espace
    temp = ft_strjoin(arrow, "  \001\033[1;34m\002"); // Bleu pour le path
    
    // Etape 2 : + Path
    prompt = ft_strjoin(temp, path);
    free(temp);
    free(path);
    
    // Etape 3 : + Fin
    temp = ft_strjoin(prompt, "\001\033[0m\002 🖕$> ");
    free(prompt);
    
    return (temp);
}

static bool	init_shell(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->token = NULL;
	shell->command = NULL;
	shell->envp = NULL;
	shell->entry = NULL;
	shell->exit_code = 0;
	shell->cmd_error_code = 0;
	shell->env = init_env(envp);
	if (!shell->env)
		return (false);
	return (true);
}

void    shell_cleanup(t_shell *shell)
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

void    loop_readline(t_shell *shell) 
{
	char *prompt_str;
	
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

void print_welcome_msg(void)
{
    printf(BOLDMAGENTA);
    printf("███╗   ███╗██╗███╗   ██╗██╗     ██████╗██╗  ██╗██╗███████╗███╗   ██╗███╗   ██╗███████╗    \n");
    printf("████╗ ████║██║████╗  ██║██║    ██╔════╝██║  ██║██║██╔════╝████╗  ██║████╗  ██║██╔════╝    \n");
    printf("██╔████╔██║██║██╔██╗ ██║██║    ██║     ███████║██║█████╗  ██╔██╗ ██║██╔██╗ ██║█████╗      \n");
    printf("██║╚██╔╝██║██║██║╚██╗██║██║    ██║     ██╔══██║██║██╔══╝  ██║╚██╗██║██║╚██╗██║██╔══╝      \n");
    printf("██║ ╚═╝ ██║██║██║ ╚████║██║    ╚██████╗██║  ██║██║███████╗██║ ╚████║██║ ╚████║███████╗    \n");
    printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝     ╚═════╝╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝    \n");
    printf("\n");
    printf(RESET);
    printf(CYAN "    Welcome to MINI CHIENNE v1.0\n" RESET);
    printf(CYAN "    Created by: [asmati & bhyant]\n\n" RESET);
}

void print_welcome_msg2(void)
{
    // Pas de rand() autorisé ? Utilise l'adresse d'une variable comme graine pseudo-aléatoire
    int seed = (long)&seed % 3; 

    if (seed == 0)
        printf(BOLDGREEN "🚀 Minishell Ready!\n" RESET);
    else if (seed == 1)
        printf(BOLDMAGENTA "🔮 Welcome back, Master.\n" RESET);
    else
        printf(BOLDCYAN "💀 System online.\n" RESET);
}

int main(int ac, char **av, char **envp)
{
    t_shell shell;

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
