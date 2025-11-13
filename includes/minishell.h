/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:30:10 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/13 13:42:43 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

volatile sig_atomic_t	g_signal; // variable globale pour gérer les signaux reçus

typedef enum	e_type_token // types de tokens
{
	PIPE,    // |
	REDIR,   // < > << >>
	WORD,    // argument/commande
}				t_type_token;

typedef enum	e_type_redir // types de redirections
{
	HEREDOC, // <<
	OUT,     // > (écrasement)
	IN,      // <
	APPEND,  // >> (ajout en fin de fichier)
}				t_type_redir;

typedef struct	s_token // liste chaînée des tokens (lexer)
{
	t_type_token	type;
	char			*str;      // contenu du token
	struct s_token	*next;
}				t_token;

typedef struct	s_redirection // liste chaînée des redirections d'une commande
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

typedef struct	s_shell // contexte global du minishell
{
	t_env						*env;      // environnement du shell
	t_token						*token;    // tokens après lexer
	t_command					*command;  // commandes après parsing
	char						**envp;    // copie tableau env (pour execve)
	int							exit_code;     // code de retour dernière commande ($?)
}				t_shell;

/*Fonction Env*/
t_env	*env_new(char *key, char *value);
t_env	*env_find(t_env *env,char *key);
char	*env_get_value(t_env *env, char *key);
void	env_set(t_env **env, char *key, char *value);
void	env_remove(t_env **env, char *key);
void env_add_back(t_env **env, t_env *new);

/*Built-In*/


#endif