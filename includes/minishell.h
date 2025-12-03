/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:17:34 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/03 05:26:42 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal;

typedef enum e_type_token // types de tokens
{
	PIPE,    // |
	REDIR,   // < > << >>
	WORD,    // argument/commande
}				t_type_token;

typedef enum e_type_quote // type de quote
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}				t_type_quote;

typedef enum e_type_redir // types de redirections
{
	HEREDOC, // <<
	OUT,     // > (écrasement)
	IN,      // <
	APPEND,  // >> (ajout en fin de fichier)
}				t_type_redir;

typedef struct s_token // liste chaînée des tokens (lexer)
{
	t_type_token	type;
	t_type_quote	quote_type;
	char			*str;      // contenu du token
	struct s_token	*next;
}				t_token;

typedef struct s_redirection // liste chaînée des redirections d'une commande
{
	char					*file;  // nom du fichier cible
	t_type_redir			type;
	struct s_redirection	*next;
}				t_redir;

typedef struct s_command // commande avec ses arguments et redirections
{
	t_redir				*redir;  // liste des redirections
	char				**args;  // tableau d'arguments (args[0] = commande)
	int					pid;     // PID du processus fils lors de l'exécution
	struct s_command	*next;   // commande suivante (après pipe)
}				t_command;

typedef struct s_env // liste chaînée de l'environnement (variables)
{
	char						*key;    // nom de la variable (ex: PATH)
	char						*value;  // valeur (ex: /usr/bin:/bin)
	struct s_env				*next;
}								t_env;

typedef struct s_shell // contexte global du minishell
{
	t_env						*env;      // environnement du shell
	t_token						*token;    // tokens après lexer
	t_command					*command;  // commandes après parsing
	char						**envp;    // copie tableau env (pour execve)
	int							exit_code;     // code de retour dernière commande ($?)
}				t_shell;

/* Fonction Env */
t_env	*env_new(char *key, char *value);
t_env	*env_find(t_env *env, char *key);
char	*env_get_value(t_env *env, char *key);
void	env_set(t_env **env, char *key, char *value);
void	env_remove(t_env **env, char *key);
void	env_add_back(t_env **env, t_env *new);
t_env	*init_env(char **envp);
bool	add_to_env_list(t_env **env_list, char *key, char *value);
char	**create_env(t_env *env);

/* Cleanup */
void	free_envp(char **envp);
void	free_env(t_env *env);
void	free_redir(t_redir *redir);
void	free_command(t_command *cmd);
void	free_array(char **array, int count);

/* Signal */
void	shell_signal(int signal);
void	signal_selector(int mode);

/* Parsing */
bool	parsing(char *entry, t_shell *shell);
bool	parse_entry(char *entry);
bool	check_closed_quote(char *entry, size_t *i);
bool	check_after_pipe(char *entry, size_t *i);
bool	check_redir(char *entry, size_t *i);
bool	check_redir_and_pipe(char *entry, size_t *i);
bool	check_pipe_operator(char *entry, size_t i);
bool	check_redir_operator(char *entry, size_t i);
bool	check_pipe_token(char *entry, size_t *i);
bool	check_and_token(char *entry, size_t *i);

/* Main */
void	loop_readline(t_shell *shell, char *entry);
void	shell_cleanup(t_shell *shell);

/* Expansion */
char	*get_var_name(char *str, int *i);
char	*get_var_value(char *name, t_env *env, int exit_code);
int		calculate_new_len(char *str, char *value, int var_len);
char	*replace_in_str(char *str, char *value, int start, int var_len);
char	*expand_variables(char *str, t_env *env, int exit_code);
void	expand_tokens(t_token *token, t_env *env, int exit_code);

/* Tokenisation */
t_token	*tokenize(char *entry);
void	add_quote_type(t_token *token);
t_token	*token_new(t_type_token type, char *str);
t_token	*token_last(t_token *tokens);
void	token_add_back(t_token **lst, t_token *new);
void	ft_tokenclear(t_token **token);
t_token	*create_pipe_token(void);
t_token	*create_redir_token(char *entry, size_t *i);
char	*extract_quoted(char *entry, size_t *i, char quote);

/* Quotes */
char	*remove_quotes(char *str, t_type_quote quote_type);
void	process_quotes(t_token *token);

/* Command Building */
t_command	*create_new_command(void);
void		add_command_back(t_command **list, t_command *new);
int			count_args_until_pipe(t_token *tokens);
t_redir		*create_redir(t_type_redir type, char *file);
void		add_redir_back(t_redir **list, t_redir *new);
t_type_redir	get_redir_type(char *str);
bool		process_redir(t_token **current, t_command *cmd);
t_command	*build_commands(t_token *tokens);

/* Built-In */
int		builtin_cd(t_shell *shell, char **args);
int		ft_echo(char **args);
int		is_valid_n_flag(char *str);
int		ft_env(t_env *env);
int		ft_exit(char **args, t_shell *shell);
int		is_numeric(char *str);
int		ft_export(char **args, t_env **env);
int		is_valid_identifier(char *str);
int		ft_pwd(char **args);
int		ft_unset(char **args, t_env **env);

/* Exec */
int		is_builtin(char *cmd);
int		exec_builtin(char **args, t_shell *shell);
char	*find_command_path(char *cmd, t_shell *shell);
int		exec_external(char **args, t_shell *shell);
int		execute_command(char **args, t_shell *shell);

int     exec_commands(t_shell *shell);
void    handle_child(t_command *cmd, t_shell *shell, int pipefd[2], int prev_fd);
int     handle_parent(int pipefd[2], int *prev_fd, t_command *cmd);
int	apply_redirections(t_redir *redir, t_shell *shell);

/* Heredoc */
int		handle_heredoc(char *delimiter, t_shell *shell);

#endif
