/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:34:23 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/11/13 13:30:42 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	pipe_error(void)
{
	return (printf("bash: syntax error near unexpected token `|'"), 0);
}

int	redir_error(void)
{
	return (printf("bash: syntax error near unexpected token `newline'"), 0);
}

int	quote_error(void)
{
	return (printf("Syntax error : quote must be closed"), 0);
}

// faire les autre message d'erreur possible