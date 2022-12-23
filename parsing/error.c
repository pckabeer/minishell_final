/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:10:45 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/23 20:17:09 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error(void)
{
	g_msv.i = 0;
	ft_putstr_fd("\033[0;31m", 2);
	if (g_msv.parse_error == 1)
	{
		ft_putstr_fd("minishell: command not found: ", 1);
		while (g_msv.rline[g_msv.i] != ' ' && g_msv.rline[g_msv.i] != '\0')
			ft_putchar_fd(g_msv.rline[g_msv.i++], 1);
	}
	else if (g_msv.parse_error == 2)
		ft_putstr_fd("minishell: parse error near ' ", 1);
	else if (g_msv.parse_error == 3)
		ft_putstr_fd("minishell: parse error near \" ", 1);
	else if (g_msv.parse_error == 4)
		ft_putstr_fd("minishell:  parse error near `>' ", 1);
	else if (g_msv.parse_error == 5)
		ft_putstr_fd("minishell:  parse error near `<' ", 1);
	else if (g_msv.parse_error == 6)
		ft_putstr_fd("minishell:  parse error near `|' ", 1);
	else if (g_msv.parse_error == 7)
		ft_putstr_fd("minishell:  syntax error near unexpected token `|' ", 1);
		g_msv.exit_status = 258;
	if(g_msv.parse_error != 121)
		ft_putchar_fd('\n', 1);
	ft_putstr_fd("\033[0m", 2);
}

void	clean_exit(void)
{
	free(g_msv.rline);
	printf("\n \033[1;34mminishell exited .... \033[0m");
	exit(0);
}
