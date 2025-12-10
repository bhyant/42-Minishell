/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:17:34 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/12/10 15:35:28 by tbhuiyan         ###   ########.fr       */
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

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BOLDBLACK "\033[1m\033[30m"
# define BOLDRED "\033[1m\033[31m"
# define BOLDGREEN "\033[1m\033[32m"
# define BOLDYELLOW "\033[1m\033[33m"
# define BOLDBLUE "\033[1m\033[34m"
# define BOLDMAGENTA "\033[1m\033[35m"
# define BOLDCYAN "\033[1m\033[36m"
# define BOLDWHITE "\033[1m\033[37m"

extern volatile sig_atomic_t	g_signal;

typedef enum e_type_token
{
	PIPE,
	REDIR,
	WORD,
}								t_type_token;

typedef enum e_type_quote
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}								t_type_quote;

typedef enum e_type_redir
{
	HEREDOC,
	OUT,
	IN,
	APPEND,
}								t_type_redir;

typedef struct s_token
{
	t_type_token				type;
	t_type_quote				quote_type;
	char						*str;
	struct s_token				*next;
}								t_token;

typedef struct s_redirection
{
	char						*file;
	t_type_redir				type;
	int							heredoc_fd;
	struct s_redirection		*next;
}								t_redir;

typedef struct s_command
{
	t_redir						*redir;
	char						**args;
	int							pid;
	struct s_command			*next;
}								t_command;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_shell
{
	t_env						*env;
	t_token						*token;
	t_command					*command;
	char						**envp;
	char						*entry;
	int							exit_code;
	int							cmd_error_code;
}								t_shell;

typedef struct s_heredoc
{
	int		fd;
	char	*delimiter;
	int		expand;
	t_shell	*shell;
}	t_heredoc;

/* Fonction Env */
t_env							*env_new(char *key, char *value);
t_env							*env_find(t_env *env, char *key);
char							*env_get_value(t_env *env, char *key);
void							env_set(t_env **env, char *key, char *value);
void							env_remove(t_env **env, char *key);
void							env_add_back(t_env **env, t_env *new);
t_env							*init_env(char **envp);
t_env							*create_minimal_env(void);
bool							add_to_env_list(t_env **env_list, char *key,
									char *value);
char							**create_env(t_env *env);

/* Cleanup */
void							free_envp(char **envp);
void							free_env(t_env *env);
void							free_redir(t_redir *redir);
void							free_command(t_command *cmd);
void							free_array(char **array, int count);

/* Signal */
void							shell_signal(int signal);
void							signal_selector(int mode);

/* Parsing */
bool							parsing(char *entry, t_shell *shell);
bool							parse_entry(char *entry);
bool							check_closed_quote(char *entry, size_t *i);
bool							check_after_pipe(char *entry, size_t *i);
bool							check_redir(char *entry, size_t *i);
bool							check_redir_and_pipe(char *entry, size_t *i);
bool							check_pipe_operator(char *entry, size_t i);
bool							check_redir_operator(char *entry, size_t i);
bool							check_pipe_token(char *entry, size_t *i);
bool							check_and_token(char *entry, size_t *i);

/* Main */
void							loop_readline(t_shell *shell);
void							shell_cleanup(t_shell *shell);
void							execute_and_cleanup(t_shell *shell);
void							cleanup_iteration(t_shell *shell);
void							print_welcome_msg(void);
void							print_welcome_msg2(void);
bool							init_shell(t_shell *shell, char **envp);
char							*get_prompt(t_shell *shell);

/* Expansion */
char							*get_var_name(char *str, int *i);
char							*get_var_value(char *name, t_env *env,
									int exit_code);
int								calculate_new_len(char *str, char *value,
									int var_len);
char							*replace_in_str(char *str, char *value,
									int start, int var_len);
char							*expand_variables(char *str, t_env *env,
									int exit_code);
void							expand_tokens(t_token *token, t_env *env,
									int exit_code);

/* Tokenisation */
t_token							*tokenize(char *entry);
void							add_quote_type(t_token *token);
t_type_quote					quote_type_chooser(t_token *current,
									int has_quote);
t_token							*token_new(t_type_token type, char *str);
t_token							*token_last(t_token *tokens);
void							token_add_back(t_token **lst, t_token *new);
void							ft_tokenclear(t_token **token);
t_token							*create_pipe_token(void);
t_token							*create_redir_token(char *entry, size_t *i);
char							*extract_quoted(char *entry, size_t *i,
									char quote);

/* Tokenisation Helpers */
int								is_delimiter(char c);
char							*join_and_free(char *result, char *part);
char							*handle_quoted_part(char *entry, size_t *i,
									char *result);
char							*handle_unquoted_part(char *entry, size_t *i,
									char *result);
char							*build_composite_word(char *entry, size_t *i);

/* Quotes */
char							*remove_quotes(char *str,
									t_type_quote quote_type);
void							process_quotes(t_token *token);

/* Quotes Utils */
char							*remove_quote_section(char *str, int *i);
char							*extract_unquoted_section(char *str, int *i);
char							*join_section_to_result(char *result,
									char *section);
int								has_quotes_in_str(char *str);

/* Command Building */
t_command						*create_new_command(void);
void							add_command_back(t_command **list,
									t_command *new);
int								count_args_until_pipe(t_token *tokens);
t_redir							*create_redir(t_type_redir type, char *file);
void							add_redir_back(t_redir **list, t_redir *new);
t_type_redir					get_redir_type(char *str);
bool							process_redir(t_token **current,
									t_command *cmd);
t_command						*build_commands(t_token *tokens);

/* Built-In */
int								builtin_cd(t_shell *shell, char **args);
int								ft_echo(char **args);
int								is_valid_n_flag(char *str);
int								ft_env(t_env *env);
int								ft_exit(char **args, t_shell *shell);
int								is_numeric(char *str);
int								ft_export(char **args, t_env **env);
int								is_valid_identifier(char *str);
int								ft_export_without_args(t_env **env);
int								count_env(t_env *env);
void							sort_env_array(t_env **arr, int size);
void							print_sorted_env(t_env **arr, int size);
int								ft_pwd(char **args);
int								ft_unset(char **args, t_env **env);

/* Exec */
int								is_builtin(char *cmd);
int								exec_builtin(char **args, t_shell *shell);
char							*try_path(char **paths, char *cmd, int i);
char							*find_command_path(char *cmd, t_shell *shell);
int								exec_external(char **args, t_shell *shell);
void							exec_child_process(char **args, char *cmd_path,
									t_shell *shell);
int								execute_command(char **args, t_shell *shell);
int								exec_cmd(t_shell *shell, t_command *cmd);
void							exec_cmd_child(t_shell *shell, t_command *cmd);
int								exec_cmd_parent(t_command *cmd, int status);
int								exec_commands(t_shell *shell);
int								exec_pipeline(t_shell *shell);
void							handle_child(t_command *cmd, t_shell *shell,
									int pipefd[2], int prev_fd);
int								handle_parent(int pipefd[2], int *prev_fd,
									t_command *cmd);
int								apply_redirections(t_redir *redir,
									t_shell *shell);
int								open_redir_file(t_redir *redir);
int								apply_redir_fd(t_redir *redir, int fd);
void							handle_command_not_found(char *cmd,
									t_shell *shell);

/* Heredoc */
int								handle_heredoc(char *delimiter, t_shell *shell);
int								process_heredocs(t_command *cmd,
									t_shell *shell);
void							close_heredocs(t_command *cmd);
void							close_all_heredocs(t_shell *shell);

#endif
