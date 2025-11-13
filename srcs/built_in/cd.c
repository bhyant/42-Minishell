/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmati <asmati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:52:04 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/13 16:05:49 by asmati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_cd(t_shell *shell, char **args)
{
	char	*path; // ou jveux partir
	char	old_pwd[1024]; // on est ou mtn
	char	new_pwd[1024]; // ou on sera apres 
	// ps 1024 prcq taille max d un chemin linux

	// je recup le dossier (ou on est mtn)
	// getcdw = Get current Working Directory
	if(!getcdw(old_pwd,sizeof(old_pwd)))
		return (1);
	// Remplit old_pwd avec le chemin actuel
	// Exemple: old_pwd devient "/home/asmati/Documents"
	// etape 3 : ou jdois aller 	
	if(!args[1] || ft_strcmp(args[1],"~") == 0)
	// regarde si jai pas dargs (juste cd) ou que largs c ~
	{
		// si cd ou cd ~
		//envget cherche dans la liste le noeuf ou key = Home et return la valeur
		path = env_get_value(shell->env, "HOME");
		if(!path)
		{
			ft_putendl_fd("cd ; HOME no set", 2);
			return (1);
		}
	}
	else if(ft_strcmp(args[1], '-') == 0)
	{
		// if cd -
		path = env_get_value(shell->env, "OLDPWD");
		if(!path)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			return 1;
		}
		ft_putendl_fd(path, 1); // affiche ou jvais 
	}
	else
		path = args[1]; // cas normal cd /home
	//changer de dossier
	if(chdir(path) == -1) //fonction systeme jfais rien
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	//sauvegarder 
	env_set(&shell->env,"OLDPWD",old_pwd);
	// mettre tout a jour
	if (getcwd(new_pwd,sizeof(new_pwd)))
		env_set(&shell->env,"PWD", new_pwd);
	return (0);
}
